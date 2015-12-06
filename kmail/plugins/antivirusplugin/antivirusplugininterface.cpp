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


#include "antivirusplugininterface.h"
#include "../common/antispamwizard.h"
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>

AntiVirusPluginInterface::AntiVirusPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{

}

AntiVirusPluginInterface::~AntiVirusPluginInterface()
{

}

void AntiVirusPluginInterface::createAction(KActionCollection *ac)
{
    QAction *action = new QAction(i18n("&Anti-Virus Wizard..."), this);
    ac->addAction(QStringLiteral("antiVirusWizard"), action);
    connect(action, &QAction::triggered, this, &AntiVirusPluginInterface::slotAntiVirusWizard);
    PimCommon::ActionType type(action, PimCommon::ActionType::Tools);
    setActionType(type);
}

void AntiVirusPluginInterface::exec()
{
    slotAntiVirusWizard();
}

void AntiVirusPluginInterface::slotAntiVirusWizard()
{
    KMail::AntiSpamWizard wiz(KMail::AntiSpamWizard::AntiVirus, parentWidget());
    wiz.exec();
}
