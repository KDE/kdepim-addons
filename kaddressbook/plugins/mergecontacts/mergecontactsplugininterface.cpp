/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactsplugininterface.h"

#include <KActionCollection>
#include <KLocalizedString>
#include <QAction>
#include <QPointer>

#include "manualmerge/mergecontactsdialog.h"

MergeContactsPluginInterface::MergeContactsPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{
}

MergeContactsPluginInterface::~MergeContactsPluginInterface()
{
}

void MergeContactsPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->addAction(QStringLiteral("merge_contacts"));
    action->setText(i18n("Merge Contacts..."));
    connect(action, &QAction::triggered, this, &MergeContactsPluginInterface::slotActivated);
    PimCommon::ActionType type(action, PimCommon::ActionType::Tools);
    addActionType(type);
}

void MergeContactsPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void MergeContactsPluginInterface::setCurrentItems(const Akonadi::Item::List &items)
{
    Akonadi::Item::List onlyContactList;
    for (const Akonadi::Item &item : items) {
        if (item.isValid() && item.hasPayload<KContacts::Addressee>()) {
            onlyContactList.append(item);
        }
    }

    mListItems = onlyContactList;
}

PimCommon::GenericPluginInterface::RequireTypes MergeContactsPluginInterface::requiresFeatures() const
{
    return PimCommon::GenericPluginInterface::CurrentItems;
}

void MergeContactsPluginInterface::exec()
{
    QPointer<KABMergeContacts::MergeContactsDialog> dlg = new KABMergeContacts::MergeContactsDialog(parentWidget());
    dlg->setContacts(mListItems);
    dlg->exec();
    delete dlg;
}
