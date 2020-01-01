/*
   Copyright (C) 2015-2020 Laurent Montel <montel@kde.org>

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

#include "mergecontactsplugininterface.h"

#include <KLocalizedString>
#include <KActionCollection>
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

PimCommon::GenericPluginInterface::RequireTypes MergeContactsPluginInterface::requires() const
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
