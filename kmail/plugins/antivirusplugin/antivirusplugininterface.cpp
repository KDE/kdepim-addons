/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "antivirusplugininterface.h"
using namespace Qt::Literals::StringLiterals;

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
    auto action = new QAction(i18nc("@action", "&Anti-Virus Wizard…"), this);
    ac->addAction(u"antiVirusWizard"_s, action);
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
