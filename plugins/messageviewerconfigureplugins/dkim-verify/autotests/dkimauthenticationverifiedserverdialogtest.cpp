/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimauthenticationverifiedserverdialogtest.h"
#include "dkimauthenticationverifiedserverdialog.h"
#include "dkimauthenticationverifiedserverwidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(DKIMAuthenticationVerifiedServerDialogTest)

DKIMAuthenticationVerifiedServerDialogTest::DKIMAuthenticationVerifiedServerDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void DKIMAuthenticationVerifiedServerDialogTest::shouldHaveDefaultValues()
{
    DKIMAuthenticationVerifiedServerDialog dlg;
    QVERIFY(!dlg.windowTitle().isEmpty());

    auto mainLayout = dlg.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto mConfigureWidget = dlg.findChild<DKIMAuthenticationVerifiedServerWidget *>(QStringLiteral("mAuthenticationVerifiedWidget"));
    QVERIFY(mConfigureWidget);

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(), QDialogButtonBox::StandardButtons{QDialogButtonBox::Ok | QDialogButtonBox::Cancel});
}
