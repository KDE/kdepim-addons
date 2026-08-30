/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimauthenticationverifiedserverdialogtest.h"
#include "dkimauthenticationverifiedserverdialog.h"
#include "dkimauthenticationverifiedserverwidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
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

    const auto mainLayout = dlg.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);

    const auto mConfigureWidget = dlg.findChild<DKIMAuthenticationVerifiedServerWidget *>(u"mAuthenticationVerifiedWidget"_s);
    QVERIFY(mConfigureWidget);

    const auto buttonBox = dlg.findChild<QDialogButtonBox *>(u"buttonBox"_s);
    QVERIFY(buttonBox);
    QCOMPARE(buttonBox->standardButtons(), QDialogButtonBox::StandardButtons{QDialogButtonBox::Ok | QDialogButtonBox::Cancel});
}

#include "moc_dkimauthenticationverifiedserverdialogtest.cpp"
