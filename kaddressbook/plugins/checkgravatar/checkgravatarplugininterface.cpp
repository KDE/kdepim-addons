/*
   Copyright (C) 2015-2016 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "checkgravatarplugininterface.h"
#include "kaddressbook_checkgravatarplugin_debug.h"
#include "gravatar/widgets/gravatarupdatedialog.h"
#include <KMessageBox>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <QPointer>
#include <ItemModifyJob>

#include <KContacts/Addressee>

CheckGravatarPluginInterface::CheckGravatarPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent),
      mAction(Q_NULLPTR)
{

}

CheckGravatarPluginInterface::~CheckGravatarPluginInterface()
{

}

void CheckGravatarPluginInterface::updateActions(int numberOfSelectedItems, int numberOfSelectedCollections)
{
    Q_UNUSED(numberOfSelectedCollections);
    if (mAction) {
        mAction->setEnabled(numberOfSelectedItems > 0);
    }
}

void CheckGravatarPluginInterface::createAction(KActionCollection *ac)
{
    mAction = ac->addAction(QStringLiteral("search_gravatar"));
    mAction->setText(i18n("Check Gravatar..."));
    connect(mAction, &QAction::triggered, this, &CheckGravatarPluginInterface::slotActivated);
    PimCommon::ActionType type(mAction, PimCommon::ActionType::Tools);
    setActionType(type);
}

void CheckGravatarPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void CheckGravatarPluginInterface::setCurrentItems(const Akonadi::Item::List &items)
{
    mListItems = items;
}

PimCommon::GenericPluginInterface::RequireTypes CheckGravatarPluginInterface::requires() const
{
    return PimCommon::GenericPluginInterface::CurrentItems;
}

void CheckGravatarPluginInterface::exec()
{
    if (mListItems.isEmpty()) {
        KMessageBox::sorry(parentWidget(), i18n("You have not selected any contacts."));
    } else {
        if (mListItems.count() == 1) {
            Akonadi::Item item = mListItems.first();
            if (item.hasPayload<KContacts::Addressee>()) {
                KContacts::Addressee address = item.payload<KContacts::Addressee>();
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
                        dlg->setOriginalUrl(address.photo().url());
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

                        Akonadi::ItemModifyJob *modifyJob = new Akonadi::ItemModifyJob(item, this);
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

bool CheckGravatarPluginInterface::hasPopupMenuSupport() const
{
    return true;
}
