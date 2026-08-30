/*
   SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurecreatedialogtest.h"
#include "openurlwithconfigurecreatedialog.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(OpenUrlWithConfigureCreateDialogTest)
OpenUrlWithConfigureCreateDialogTest::OpenUrlWithConfigureCreateDialogTest(QObject *parent)
    : QObject{parent}
{
}

void OpenUrlWithConfigureCreateDialogTest::shouldHaveDefaultValues()
{
    OpenUrlWithConfigureCreateDialog dlg;
    QVERIFY(!dlg.windowTitle().isEmpty());

    const auto mainLayout = dlg.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);

    const auto mOpenUrlWithCreateWidget = dlg.findChild<OpenUrlWithConfigureCreateWidget *>(u"mOpenUrlWithCreateWidget"_s);
    QVERIFY(mOpenUrlWithCreateWidget);

    const auto buttonBox = dlg.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(), QDialogButtonBox::StandardButtons{QDialogButtonBox::Ok | QDialogButtonBox::Cancel});
}

#include "moc_openurlwithconfigurecreatedialogtest.cpp"
