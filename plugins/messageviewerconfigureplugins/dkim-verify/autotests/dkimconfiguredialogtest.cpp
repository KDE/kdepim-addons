/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimconfiguredialogtest.h"
#include "../dkimconfiguredialog.h"
#include "../dkimconfigurewidget.h"
#include <QTest>
#include <QStandardPaths>
#include <QVBoxLayout>
#include <QDialogButtonBox>

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

    auto *mainLayout = dlg.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto *mConfigureWidget = dlg.findChild<DKIMConfigureWidget *>(QStringLiteral("mConfigureWidget"));
    QVERIFY(mConfigureWidget);

    auto *buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(), {QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::RestoreDefaults});
}
