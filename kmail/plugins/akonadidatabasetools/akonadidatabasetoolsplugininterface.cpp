/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "akonadidatabasetoolsplugininterface.h"
#include "akonadidatabasetoolsjob.h"
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
    {
        auto action = new QAction(i18n("&Akonadi Vacuum..."), this);
        ac->addAction(QStringLiteral("akonadivacuum"), action);
        connect(action, &QAction::triggered, this, [this]() {
            mTool = AkonadiDatabaseToolsUtils::AkonadiDatabaseTool::Vacuum;
            slotActivated();
        });

        PimCommon::ActionType type(action, PimCommon::ActionType::Tools);
        addActionType(type);
    }
    {
        auto action = new QAction(i18n("&Akonadi Fsck..."), this);
        ac->addAction(QStringLiteral("akonadifsck"), action);
        connect(action, &QAction::triggered, this, [this]() {
            mTool = AkonadiDatabaseToolsUtils::AkonadiDatabaseTool::Fsck;
            slotActivated();
        });

        PimCommon::ActionType type(action, PimCommon::ActionType::Tools);
        addActionType(type);
    }
}

void AkonadiDatabaseToolsPluginInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void AkonadiDatabaseToolsPluginInterface::exec()
{
    AkonadiDatabaseToolsJob *job = new AkonadiDatabaseToolsJob(this);
    job->setTool(mTool);
    job->start();
}
