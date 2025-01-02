/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkbeforesendconfigurewidgettest.h"
#include "../configurewidget/checkbeforesendconfigurewidget.h"
#include <QCheckBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

CheckBeforeSendConfigureWidgetTest::CheckBeforeSendConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

CheckBeforeSendConfigureWidgetTest::~CheckBeforeSendConfigureWidgetTest() = default;

void CheckBeforeSendConfigureWidgetTest::shouldHaveDefaultValue()
{
    CheckBeforeSendConfigureWidget w(nullptr);
    auto vboxlayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(vboxlayout);

    auto mCheckPlainTextMail = w.findChild<QCheckBox *>(QStringLiteral("checkplaintext"));
    QVERIFY(mCheckPlainTextMail);
    QVERIFY(!mCheckPlainTextMail->text().isEmpty());
    QVERIFY(!mCheckPlainTextMail->isChecked());

    auto mCheckMailTransport = w.findChild<QCheckBox *>(QStringLiteral("smtpdefinedinidentity"));
    QVERIFY(mCheckMailTransport);
    QVERIFY(!mCheckMailTransport->text().isEmpty());
    QVERIFY(!mCheckMailTransport->isChecked());

    auto mCheckDuplicateEmails = w.findChild<QCheckBox *>(QStringLiteral("checkduplicatedemailsaddresses"));
    QVERIFY(mCheckDuplicateEmails);
    QVERIFY(!mCheckDuplicateEmails->text().isEmpty());
    QVERIFY(!mCheckDuplicateEmails->isChecked());

    auto mCheckSendAttachments = w.findChild<QCheckBox *>(QStringLiteral("checksendattachment"));
    QVERIFY(mCheckSendAttachments);
    QVERIFY(!mCheckSendAttachments->text().isEmpty());
    QVERIFY(!mCheckSendAttachments->isChecked());
}

void CheckBeforeSendConfigureWidgetTest::shouldResetValue()
{
    CheckBeforeSendConfigureWidget w(nullptr);

    auto mCheckPlainTextMail = w.findChild<QCheckBox *>(QStringLiteral("checkplaintext"));
    auto mCheckMailTransport = w.findChild<QCheckBox *>(QStringLiteral("smtpdefinedinidentity"));
    auto mCheckDuplicateEmails = w.findChild<QCheckBox *>(QStringLiteral("checkduplicatedemailsaddresses"));
    auto mCheckSendAttachments = w.findChild<QCheckBox *>(QStringLiteral("checksendattachment"));

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

#include "moc_checkbeforesendconfigurewidgettest.cpp"
