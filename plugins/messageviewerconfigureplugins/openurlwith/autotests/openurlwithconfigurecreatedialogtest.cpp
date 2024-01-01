/*
   SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurecreatedialogtest.h"
#include "openurlwithconfigurecreatedialog.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(OpenUrlWithConfigureCreateDialogTest)
OpenUrlWithConfigureCreateDialogTest::OpenUrlWithConfigureCreateDialogTest(QObject *parent)
    : QObject{parent}
{
}

void OpenUrlWithConfigureCreateDialogTest::shouldHaveDefaultValues()
{
    OpenUrlWithConfigureCreateDialog dlg;
    QVERIFY(!dlg.windowTitle().isEmpty());

    auto mainLayout = dlg.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto mOpenUrlWithCreateWidget = dlg.findChild<OpenUrlWithConfigureCreateWidget *>(QStringLiteral("mOpenUrlWithCreateWidget"));
    QVERIFY(mOpenUrlWithCreateWidget);

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(), QDialogButtonBox::StandardButtons{QDialogButtonBox::Ok | QDialogButtonBox::Cancel});
}

#include "moc_openurlwithconfigurecreatedialogtest.cpp"
