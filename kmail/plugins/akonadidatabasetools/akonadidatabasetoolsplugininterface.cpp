/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "akonadidatabasetoolsplugininterface.h"
#include "akonadidatasetools_debug.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <QAction>

AkonadiDatabaseToolsPluginInterface::AkonadiDatabaseToolsPluginInterface(QObject *parent)
    : PimCommon::GenericPluginInterface(parent)
{
}

AkonadiDatabaseToolsPluginInterface::~AkonadiDatabaseToolsPluginInterface() = default;

void AkonadiDatabaseToolsPluginInterface::createAction(KActionCollection *ac)
{
    auto action = new QAction(i18n("&Akonadi Vaccum..."), this);
    ac->addAction(QStringLiteral("akonadivaccum"), action);
    connect(action, &QAction::triggered, this, &AkonadiDatabaseToolsPluginInterface::slotActivated);
    PimCommon::ActionType type(action, PimCommon::ActionType::Tools);
    addActionType(type);
}

void AkonadiDatabaseToolsPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void AkonadiDatabaseToolsPluginInterface::exec()
{
    switch (mTool) {
    case Unknown:
        break;
    case Vaccum:
        break;
    case Fsck:
        break;
    }
}
