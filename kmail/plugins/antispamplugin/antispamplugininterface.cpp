/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "antispamplugininterface.h"
#include "../common/antispamwizard.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <QAction>

AntiSpamPluginInterface::AntiSpamPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{
}

AntiSpamPluginInterface::~AntiSpamPluginInterface() = default;

void AntiSpamPluginInterface::createAction(KActionCollection *ac)
{
    auto action = new QAction(i18n("&Anti-Spam Wizard..."), this);
    ac->addAction(QStringLiteral("antiSpamWizard"), action);
    connect(action, &QAction::triggered, this, &AntiSpamPluginInterface::slotActivated);
    PimCommon::ActionType type(action, PimCommon::ActionType::Tools);
    addActionType(type);
}

void AntiSpamPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void AntiSpamPluginInterface::exec()
{
    KMail::AntiSpamWizard wiz(KMail::AntiSpamWizard::AntiSpam, parentWidget());
    wiz.exec();
}
