/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkbeforesendupdatesmtpdialogtest.h"
using namespace Qt::Literals::StringLiterals;

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
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);

    auto lab = w.findChild<QLabel *>(u"label"_s);
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());

    auto mChangeSmtp = w.findChild<QCheckBox *>(u"changesmtp"_s);
    QVERIFY(mChangeSmtp);
    QVERIFY(!mChangeSmtp->isChecked());

    auto buttonBox = w.findChild<QDialogButtonBox *>(u"buttonbox"_s);
    QVERIFY(buttonBox);

    QVERIFY(!w.windowTitle().isEmpty());
}

#include "moc_checkbeforesendupdatesmtpdialogtest.cpp"
