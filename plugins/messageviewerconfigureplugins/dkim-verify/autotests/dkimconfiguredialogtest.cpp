/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimconfiguredialogtest.h"
#include "../dkimconfiguredialog.h"
#include "../dkimconfigurewidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

QTEST_MAIN(DKIMConfigureDialogTest)

DKIMConfigureDialogTest::DKIMConfigureDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void DKIMConfigureDialogTest::shouldHaveDefaultValue()
{
    DKIMConfigureDialog dlg;
    QVERIFY(!dlg.windowTitle().isEmpty());

    auto mainLayout = dlg.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto mConfigureWidget = dlg.findChild<DKIMConfigureWidget *>(QStringLiteral("mConfigureWidget"));
    QVERIFY(mConfigureWidget);

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(),
             QDialogButtonBox::StandardButtons{QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::RestoreDefaults});
}

#include "moc_dkimconfiguredialogtest.cpp"
