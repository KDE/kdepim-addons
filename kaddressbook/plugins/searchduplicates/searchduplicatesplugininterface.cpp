/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "searchduplicatesplugininterface.h"

#include <KActionCollection>
#include <KLocalizedString>
#include <QAction>
#include <QPointer>

#include "../mergelib/searchduplicate/searchandmergecontactduplicatecontactdialog.h"

SearchDuplicatesPluginInterface::SearchDuplicatesPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{
}

SearchDuplicatesPluginInterface::~SearchDuplicatesPluginInterface()
{
}

void SearchDuplicatesPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->addAction(QStringLiteral("search_duplicate_contacts"));
    action->setText(i18n("Search Duplicate Contacts..."));
    connect(action, &QAction::triggered, this, &SearchDuplicatesPluginInterface::slotActivated);
    PimCommon::ActionType type(action, PimCommon::ActionType::Tools);
    addActionType(type);
}

void SearchDuplicatesPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void SearchDuplicatesPluginInterface::exec()
{
    QPointer<KABMergeContacts::SearchAndMergeContactDuplicateContactDialog> dlg =
        new KABMergeContacts::SearchAndMergeContactDuplicateContactDialog(parentWidget());
    dlg->searchPotentialDuplicateContacts(mListItems);
    dlg->exec();
    delete dlg;
}

void SearchDuplicatesPluginInterface::setItems(const Akonadi::Item::List &items)
{
    Akonadi::Item::List onlyContactList;
    for (const Akonadi::Item &item : items) {
        if (item.isValid() && item.hasPayload<KContacts::Addressee>()) {
            onlyContactList.append(item);
        }
    }

    mListItems = onlyContactList;
}

PimCommon::GenericPluginInterface::RequireTypes SearchDuplicatesPluginInterface::requiresFeatures() const
{
    return PimCommon::GenericPluginInterface::Items;
}
