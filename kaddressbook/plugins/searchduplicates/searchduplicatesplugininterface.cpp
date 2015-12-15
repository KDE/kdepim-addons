/*
  Copyright (c) 2015 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "searchduplicatesplugininterface.h"

#include <KLocalizedString>
#include <KActionCollection>
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
    setActionType(type);
}

void SearchDuplicatesPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void SearchDuplicatesPluginInterface::exec()
{
    QPointer<KABMergeContacts::SearchAndMergeContactDuplicateContactDialog> dlg = new KABMergeContacts::SearchAndMergeContactDuplicateContactDialog(parentWidget());
    dlg->searchPotentialDuplicateContacts(mListItems);
    dlg->exec();
    delete dlg;
}

void SearchDuplicatesPluginInterface::setCurrentItems(const Akonadi::Item::List &items)
{
    Akonadi::Item::List onlyContactList;
    Q_FOREACH(const Akonadi::Item &item, items) {
        if (item.isValid() && item.hasPayload<KContacts::Addressee>()) {
            onlyContactList.append(item);
        }
    }

    mListItems = onlyContactList;
}

PimCommon::GenericPluginInterface::RequireTypes SearchDuplicatesPluginInterface::requires() const
{
    return PimCommon::GenericPluginInterface::CurrentItems;
}
