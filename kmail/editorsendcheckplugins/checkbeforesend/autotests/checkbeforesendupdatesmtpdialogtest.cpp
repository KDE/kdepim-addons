/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkbeforesendupdatesmtpdialogtest.h"
#include "checkbeforesendupdatesmtpdialog.h"
#include <QCheckBox>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QTest>
QTEST_MAIN(CheckBeforeSendUpdateSmtpDialogTest)

CheckBeforeSendUpdateSmtpDialogTest::CheckBeforeSendUpdateSmtpDialogTest(QObject *parent)
    : QObject(parent)
{
}

void CheckBeforeSendUpdateSmtpDialogTest::shouldHaveDefaultValue()
{
    CheckBeforeSendUpdateSmtpDialog w;
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    QLabel *lab = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());

    QCheckBox *mChangeSmtp = w.findChild<QCheckBox *>(QStringLiteral("changesmtp"));
    QVERIFY(mChangeSmtp);
    QVERIFY(!mChangeSmtp->isChecked());

    QDialogButtonBox *buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    QVERIFY(!w.windowTitle().isEmpty());
}
