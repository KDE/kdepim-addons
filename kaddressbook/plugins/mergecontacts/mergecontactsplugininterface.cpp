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

MergeContactsPluginInterface::MergeContactsPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{

}

MergeContactsPluginInterface::~MergeContactsPluginInterface()
{

}

void MergeContactsPluginInterface::createAction(KActionCollection *ac)
{
    //TODO
    /*
    QAction *action = new QAction(i18n("&Anti-Spam Wizard..."), this);
    ac->addAction(QStringLiteral("antiSpamWizard"), action);
    connect(action, &QAction::triggered, this, &MergeContactsPluginInterface::slotActivated);
    PimCommon::ActionType type(action, PimCommon::ActionType::Tools);
    setActionType(type);
    */
}

void MergeContactsPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void MergeContactsPluginInterface::setCurrentItems(const Akonadi::Item::List &items)
{
    //TODO
}

PimCommon::GenericPluginInterface::RequireTypes MergeContactsPluginInterface::requires() const
{
    return PimCommon::GenericPluginInterface::CurrentItems;
}

void MergeContactsPluginInterface::exec()
{
    //TODO
}
