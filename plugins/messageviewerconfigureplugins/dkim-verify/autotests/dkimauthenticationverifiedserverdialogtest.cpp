/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimauthenticationverifiedserverdialogtest.h"
#include "dkimauthenticationverifiedserverdialog.h"
#include "dkimauthenticationverifiedserverwidget.h"
#include <QTest>
#include <QStandardPaths>
#include <QVBoxLayout>
#include <QDialogButtonBox>
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

    auto *mainLayout = dlg.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto *mConfigureWidget = dlg.findChild<DKIMAuthenticationVerifiedServerWidget *>(QStringLiteral("mAuthenticationVerifiedWidget"));
    QVERIFY(mConfigureWidget);

    auto *buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonBox"));
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(), {QDialogButtonBox::Ok | QDialogButtonBox::Cancel});
}
