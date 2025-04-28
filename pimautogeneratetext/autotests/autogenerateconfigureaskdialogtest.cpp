/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateconfigureaskdialogtest.h"
#include "autogenerateconfigureaskdialog.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(AutogenerateConfigureAskDialogTest)

AutogenerateConfigureAskDialogTest::AutogenerateConfigureAskDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void AutogenerateConfigureAskDialogTest::shouldHaveDefaultValues()
{
    AutogenerateConfigureAskDialog w;
    // TODO
}

#include "moc_autogenerateconfigureaskdialogtest.cpp"
