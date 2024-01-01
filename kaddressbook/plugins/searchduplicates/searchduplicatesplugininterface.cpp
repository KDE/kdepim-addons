/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "searchduplicatesplugininterface.h"
#include "searchduplicate/searchandmergecontactduplicatecontactdialog.h"

#include <KActionCollection>
#include <KLocalizedString>
#include <QAction>

SearchDuplicatesPluginInterface::SearchDuplicatesPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{
}

SearchDuplicatesPluginInterface::~SearchDuplicatesPluginInterface() = default;

void SearchDuplicatesPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = ac->addAction(QStringLiteral("search_duplicate_contacts"));
    action->setText(i18n("Search Duplicate Contacts..."));
    connect(action, &QAction::triggered, this, &SearchDuplicatesPluginInterface::slotActivated);
    const PimCommon::ActionType type(action, PimCommon::ActionType::Tools);
    addActionType(type);
}

void SearchDuplicatesPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void SearchDuplicatesPluginInterface::exec()
{
    KABMergeContacts::SearchAndMergeContactDuplicateContactDialog dlg(parentWidget());
    dlg.searchPotentialDuplicateContacts(mListItems);
    dlg.exec();
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
