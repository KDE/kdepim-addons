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

#include "mergecontactsplugininterface.h"

#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <QPointer>

#include "../mergelib/searchduplicate/searchandmergecontactduplicatecontactdialog.h"

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
    setActionType(type);
}

void MergeContactsPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void MergeContactsPluginInterface::setCurrentItems(const Akonadi::Item::List &items)
{
    mListItems = items;
}

PimCommon::GenericPluginInterface::RequireTypes MergeContactsPluginInterface::requires() const
{
    return PimCommon::GenericPluginInterface::CurrentItems;
}

void MergeContactsPluginInterface::exec()
{
    if (mListItems.isEmpty())
        return;
    QPointer<KABMergeContacts::SearchAndMergeContactDuplicateContactDialog> dlg = new KABMergeContacts::SearchAndMergeContactDuplicateContactDialog(parentWidget());
    dlg->searchPotentialDuplicateContacts(mListItems);
    dlg->exec();
    delete dlg;
}
