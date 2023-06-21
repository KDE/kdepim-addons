/*
   SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfiguredialogtest.h"
#include "openurlwithconfiguredialog.h"
#include "openurlwithconfigurewidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(OpenUrlWithConfigureDialogTest)
OpenUrlWithConfigureDialogTest::OpenUrlWithConfigureDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void OpenUrlWithConfigureDialogTest::shouldHaveDefaultValues()
{
    OpenUrlWithConfigureDialog dlg;
    QVERIFY(!dlg.windowTitle().isEmpty());

    auto mainLayout = dlg.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto mConfigureWidget = dlg.findChild<OpenUrlWithConfigureWidget *>(QStringLiteral("mOpenUrlWithWidget"));
    QVERIFY(mConfigureWidget);

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(), QDialogButtonBox::StandardButtons{QDialogButtonBox::Ok | QDialogButtonBox::Cancel});
}

#include "moc_openurlwithconfiguredialogtest.cpp"
