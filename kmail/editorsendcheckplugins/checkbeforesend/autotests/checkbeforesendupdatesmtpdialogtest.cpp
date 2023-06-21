/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkbeforesendupdatesmtpdialogtest.h"
#include "checkbeforesendupdatesmtpdialog.h"
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(CheckBeforeSendUpdateSmtpDialogTest)

CheckBeforeSendUpdateSmtpDialogTest::CheckBeforeSendUpdateSmtpDialogTest(QObject *parent)
    : QObject(parent)
{
}

void CheckBeforeSendUpdateSmtpDialogTest::shouldHaveDefaultValue()
{
    CheckBeforeSendUpdateSmtpDialog w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto lab = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());

    auto mChangeSmtp = w.findChild<QCheckBox *>(QStringLiteral("changesmtp"));
    QVERIFY(mChangeSmtp);
    QVERIFY(!mChangeSmtp->isChecked());

    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    QVERIFY(!w.windowTitle().isEmpty());
}

#include "moc_checkbeforesendupdatesmtpdialogtest.cpp"
