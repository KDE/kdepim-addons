/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateconfigureaskdialogtest.h"
#include "autogenerateconfigureaskdialog.h"
#include "autogenerateconfigureaskwidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(AutogenerateConfigureAskDialogTest)

AutogenerateConfigureAskDialogTest::AutogenerateConfigureAskDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void AutogenerateConfigureAskDialogTest::shouldHaveDefaultValues()
{
    AutogenerateConfigureAskDialog w;

    QVERIFY(!w.windowTitle().isEmpty());
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mAutogenerateConfigureAskWidget = w.findChild<AutogenerateConfigureAskWidget *>(QStringLiteral("mAutogenerateConfigureAskWidget"));
    QVERIFY(mAutogenerateConfigureAskWidget);

    auto button = w.findChild<QDialogButtonBox *>(QStringLiteral("button"));
    QVERIFY(button);
}

#include "moc_autogenerateconfigureaskdialogtest.cpp"
