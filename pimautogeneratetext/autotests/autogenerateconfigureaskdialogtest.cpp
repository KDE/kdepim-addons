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
using namespace Qt::Literals::StringLiterals;
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
    const auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    const auto mAutogenerateConfigureAskWidget = w.findChild<AutogenerateConfigureAskWidget *>(u"mAutogenerateConfigureAskWidget"_s);
    QVERIFY(mAutogenerateConfigureAskWidget);

    const auto button = w.findChild<QDialogButtonBox *>(u"button"_s);
    QVERIFY(button);
}

#include "moc_autogenerateconfigureaskdialogtest.cpp"
