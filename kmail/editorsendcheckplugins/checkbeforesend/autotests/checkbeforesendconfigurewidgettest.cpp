/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "checkbeforesendconfigurewidgettest.h"
#include "../configurewidget/checkbeforesendconfigurewidget.h"
#include <QTest>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QStandardPaths>

CheckBeforeSendConfigureWidgetTest::CheckBeforeSendConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

CheckBeforeSendConfigureWidgetTest::~CheckBeforeSendConfigureWidgetTest()
{
}

void CheckBeforeSendConfigureWidgetTest::shouldHaveDefaultValue()
{
    CheckBeforeSendConfigureWidget w(nullptr);
    QVBoxLayout *vboxlayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(vboxlayout);

    QCheckBox *mCheckPlainTextMail = w.findChild<QCheckBox *>(QStringLiteral("checkplaintext"));
    QVERIFY(mCheckPlainTextMail);
    QVERIFY(!mCheckPlainTextMail->text().isEmpty());
    QVERIFY(!mCheckPlainTextMail->isChecked());

    QCheckBox *mCheckMailTransport = w.findChild<QCheckBox *>(QStringLiteral("smtpdefinedinidentity"));
    QVERIFY(mCheckMailTransport);
    QVERIFY(!mCheckMailTransport->text().isEmpty());
    QVERIFY(!mCheckMailTransport->isChecked());

    QCheckBox *mCheckDuplicateEmails = w.findChild<QCheckBox *>(QStringLiteral("checkduplicatedemailsaddresses"));
    QVERIFY(mCheckDuplicateEmails);
    QVERIFY(!mCheckDuplicateEmails->text().isEmpty());
    QVERIFY(!mCheckDuplicateEmails->isChecked());

    QCheckBox *mCheckSendAttachments = w.findChild<QCheckBox *>(QStringLiteral("checksendattachment"));
    QVERIFY(mCheckSendAttachments);
    QVERIFY(!mCheckSendAttachments->text().isEmpty());
    QVERIFY(!mCheckSendAttachments->isChecked());
}

void CheckBeforeSendConfigureWidgetTest::shouldResetValue()
{
    CheckBeforeSendConfigureWidget w(nullptr);

    QCheckBox *mCheckPlainTextMail = w.findChild<QCheckBox *>(QStringLiteral("checkplaintext"));
    QCheckBox *mCheckMailTransport = w.findChild<QCheckBox *>(QStringLiteral("smtpdefinedinidentity"));
    QCheckBox *mCheckDuplicateEmails = w.findChild<QCheckBox *>(QStringLiteral("checkduplicatedemailsaddresses"));
    QCheckBox *mCheckSendAttachments = w.findChild<QCheckBox *>(QStringLiteral("checksendattachment"));

    mCheckMailTransport->setChecked(true);
    mCheckDuplicateEmails->setChecked(true);
    mCheckSendAttachments->setChecked(true);
    mCheckPlainTextMail->setChecked(true);

    QVERIFY(mCheckPlainTextMail->isChecked());
    QVERIFY(mCheckMailTransport->isChecked());
    QVERIFY(mCheckDuplicateEmails->isChecked());
    QVERIFY(mCheckSendAttachments->isChecked());

    mCheckMailTransport->setChecked(false);
    mCheckDuplicateEmails->setChecked(false);
    mCheckSendAttachments->setChecked(false);
    mCheckPlainTextMail->setChecked(false);

    QVERIFY(!mCheckPlainTextMail->isChecked());
    QVERIFY(!mCheckMailTransport->isChecked());
    QVERIFY(!mCheckDuplicateEmails->isChecked());
    QVERIFY(!mCheckSendAttachments->isChecked());

    mCheckMailTransport->setChecked(true);
    mCheckDuplicateEmails->setChecked(true);
    mCheckSendAttachments->setChecked(true);
    mCheckPlainTextMail->setChecked(true);

    w.resetSettings();
    QVERIFY(!mCheckPlainTextMail->isChecked());
    QVERIFY(!mCheckMailTransport->isChecked());
    QVERIFY(!mCheckDuplicateEmails->isChecked());
    QVERIFY(!mCheckSendAttachments->isChecked());
}

QTEST_MAIN(CheckBeforeSendConfigureWidgetTest)
