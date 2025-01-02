/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "quicktextconfiguredialogtest.h"
#include "quicktextconfiguredialog.h"
#include "quicktextconfigurewidget.h"
#include <QVBoxLayout>

#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(QuickTextConfigureDialogTest)

QuickTextConfigureDialogTest::QuickTextConfigureDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void QuickTextConfigureDialogTest::shouldHaveDefaultValues()
{
    QuickTextConfigureDialog dlg;

    auto mainLayout = dlg.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto mQuickTextConfigureWidget = dlg.findChild<QuickTextConfigureWidget *>(QStringLiteral("quicktextconfigurewidget"));
    QVERIFY(mQuickTextConfigureWidget);

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);
}

#include "moc_quicktextconfiguredialogtest.cpp"
