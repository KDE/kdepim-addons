/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkgravatarplugininterface.h"
#include "gravatar/widgets/gravatarupdatedialog.h"
#include "kaddressbook_checkgravatarplugin_debug.h"
#include <Akonadi/ItemModifyJob>
#include <KActionCollection>
#include <KLocalizedString>
#include <KMessageBox>
#include <QAction>
#include <QPointer>

#include <KContacts/Addressee>

CheckGravatarPluginInterface::CheckGravatarPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{
}

CheckGravatarPluginInterface::~CheckGravatarPluginInterface() = default;

void CheckGravatarPluginInterface::updateActions(int numberOfSelectedItems, int numberOfSelectedCollections)
{
    Q_UNUSED(numberOfSelectedCollections)
    if (mAction) {
        mAction->setEnabled(numberOfSelectedItems > 0);
    }
}

void CheckGravatarPluginInterface::createAction(KActionCollection *ac)
{
    mAction = ac->addAction(QStringLiteral("search_gravatar"));
    mAction->setText(i18n("Check Gravatar…"));
    connect(mAction, &QAction::triggered, this, &CheckGravatarPluginInterface::slotActivated);
    PimCommon::ActionType type(mAction, PimCommon::ActionType::Tools);
    addActionType(type);
}

void CheckGravatarPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void CheckGravatarPluginInterface::setCurrentItems(const Akonadi::Item::List &items)
{
    mListItems = items;
}

PimCommon::GenericPluginInterface::RequireTypes CheckGravatarPluginInterface::requiresFeatures() const
{
    return PimCommon::GenericPluginInterface::CurrentItems;
}

void CheckGravatarPluginInterface::exec()
{
    if (mListItems.isEmpty()) {
        KMessageBox::error(parentWidget(), i18n("You have not selected any contacts."));
    } else {
        if (mListItems.count() == 1) {
            Akonadi::Item item = mListItems.constFirst();
            if (item.hasPayload<KContacts::Addressee>()) {
                auto address = item.payload<KContacts::Addressee>();
                const QString email = address.preferredEmail();
                if (email.isEmpty()) {
                    KMessageBox::error(parentWidget(), i18n("No email found for this contact."));
                    return;
                }
                QPointer<KABGravatar::GravatarUpdateDialog> dlg = new KABGravatar::GravatarUpdateDialog(parentWidget());
                dlg->setEmail(email);
                if (!address.photo().isEmpty()) {
                    if (address.photo().isIntern()) {
                        const QPixmap pix = QPixmap::fromImage(address.photo().data());
                        dlg->setOriginalPixmap(pix);
                    } else {
                        dlg->setOriginalUrl(QUrl(address.photo().url()));
                    }
                }
                if (dlg->exec()) {
                    KContacts::Picture picture = address.photo();
                    bool needToSave = false;
                    if (dlg->saveUrl()) {
                        const QUrl url = dlg->resolvedUrl();
                        if (!url.isEmpty()) {
                            picture.setUrl(url.toString());
                            needToSave = true;
                        }
                    } else {
                        const QPixmap pix = dlg->pixmap();
                        if (!pix.isNull()) {
                            picture.setData(pix.toImage());
                            needToSave = true;
                        }
                    }
                    if (needToSave) {
                        address.setPhoto(picture);
                        item.setPayload<KContacts::Addressee>(address);

                        auto modifyJob = new Akonadi::ItemModifyJob(item, this);
                        connect(modifyJob, &Akonadi::ItemModifyJob::result, this, &CheckGravatarPluginInterface::slotModifyContactFinished);
                    }
                }
                delete dlg;
            } else {
                KMessageBox::information(parentWidget(), i18n("A contact group was selected."));
            }
        } else {
            KMessageBox::information(parentWidget(), i18n("Too many contacts selected."));
        }
    }
}

void CheckGravatarPluginInterface::slotModifyContactFinished(KJob *job)
{
    if (job->error()) {
        qCDebug(KADDRESSBOOK_CHECKGRAVATAR_LOG) << "Error while modifying items. " << job->error() << job->errorString();
    }
}

#include "moc_checkgravatarplugininterface.cpp"
