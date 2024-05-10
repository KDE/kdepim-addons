/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "antivirusplugininterface.h"
#include "../common/antispamwizard.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <QAction>

AntiVirusPluginInterface::AntiVirusPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{
}

AntiVirusPluginInterface::~AntiVirusPluginInterface() = default;

void AntiVirusPluginInterface::createAction(KActionCollection *ac)
{
    auto action = new QAction(i18n("&Anti-Virus Wizard…"), this);
    ac->addAction(QStringLiteral("antiVirusWizard"), action);
    connect(action, &QAction::triggered, this, &AntiVirusPluginInterface::slotActivated);
    PimCommon::ActionType type(action, PimCommon::ActionType::Tools);
    addActionType(type);
}

void AntiVirusPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void AntiVirusPluginInterface::exec()
{
    KMail::AntiSpamWizard wiz(KMail::AntiSpamWizard::AntiVirus, parentWidget());
    wiz.exec();
}
