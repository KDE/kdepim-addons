/*
   SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "akonadidatabasetoolsplugininterface.h"
#include "akonadidatabasetoolsdialog.h"
#include "akonadidatabasetoolsjob.h"
#include "akonadidatasetools_debug.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <KMessageBox>
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
            if (KMessageBox::warningTwoActions(parentWidget(),
                                               i18n("Do you want to vacuum akonadi database?"),
                                               i18nc("@title:window", "Akonadi Vacuum"),
                                               KGuiItem(i18n("Vacuum")),
                                               KStandardGuiItem::cancel())
                == KMessageBox::ButtonCode::PrimaryAction) {
                mTool = AkonadiDatabaseToolsUtils::AkonadiDatabaseTool::Vacuum;
                slotActivated();
            }
        });

        PimCommon::ActionType type(action, PimCommon::ActionType::Tools);
        addActionType(type);
    }
    {
        auto action = new QAction(i18n("&Akonadi Fsck..."), this);
        ac->addAction(QStringLiteral("akonadifsck"), action);
        connect(action, &QAction::triggered, this, [this]() {
            if (KMessageBox::warningTwoActions(

                    parentWidget(),
                    i18n("Do you want to fsck akonadi database?"),
                    i18nc("@title:window", "Akonadi Fsck"),
                    KGuiItem(i18n("Fsck")),
                    KStandardGuiItem::cancel())
                == KMessageBox::ButtonCode::PrimaryAction) {
                mTool = AkonadiDatabaseToolsUtils::AkonadiDatabaseTool::Fsck;
                slotActivated();
            }
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
    auto dlg = new AkonadiDatabaseToolsDialog(parentWidget());
    switch (mTool) {
    case AkonadiDatabaseToolsUtils::AkonadiDatabaseTool::Fsck:
        dlg->setWindowTitle(i18nc("@title:window", "Akonadi Fsck"));
        break;
    case AkonadiDatabaseToolsUtils::AkonadiDatabaseTool::Vacuum:
        dlg->setWindowTitle(i18nc("@title:window", "Akonadi Vacuum"));
        break;
    case AkonadiDatabaseToolsUtils::AkonadiDatabaseTool::Unknown:
        qCWarning(AKONADIDATABASETOOLS_LOG) << "Tool is unknown it's a bug";
        break;
    }

    dlg->show();
    auto job = new AkonadiDatabaseToolsJob(this);
    job->setTool(mTool);
    connect(job, &AkonadiDatabaseToolsJob::receivedStandardError, dlg, &AkonadiDatabaseToolsDialog::appendErrorText);
    connect(job, &AkonadiDatabaseToolsJob::receivedStandardOutput, dlg, &AkonadiDatabaseToolsDialog::appendText);
    connect(job, &AkonadiDatabaseToolsJob::finished, dlg, [dlg]() {
        dlg->appendText(QStringLiteral("---------"));
        dlg->appendText(i18n("Finished."));
    });
    dlg->appendText(i18n("Start..."));
    dlg->appendText(QStringLiteral("---------"));
    job->start();
}
