/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "autogenerateconfigureaskdialog.h"
#include "autogenerateconfigureaskmanager.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QStandardPaths>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    QCommandLineParser parser;
    parser.addVersionOption();
    parser.addHelpOption();
    parser.process(app);

    AutogenerateConfigureAskDialog dlg;
    AutogenerateConfigureAskManager *manager = new AutogenerateConfigureAskManager(&dlg);
    manager->load();
    dlg.setAskInfos(manager->askInfos());
    if (dlg.exec()) {
        manager->setInfos(dlg.askInfos());
        manager->save();
    }
    return 0;
}
