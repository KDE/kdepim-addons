/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkbeforesendconfigurewidgettest.h"
using namespace Qt::Literals::StringLiterals;

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
    auto vboxlayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(vboxlayout);

    auto mCheckPlainTextMail = w.findChild<QCheckBox *>(u"checkplaintext"_s);
    QVERIFY(mCheckPlainTextMail);
    QVERIFY(!mCheckPlainTextMail->text().isEmpty());
    QVERIFY(!mCheckPlainTextMail->isChecked());

    auto mCheckMailTransport = w.findChild<QCheckBox *>(u"smtpdefinedinidentity"_s);
    QVERIFY(mCheckMailTransport);
    QVERIFY(!mCheckMailTransport->text().isEmpty());
    QVERIFY(!mCheckMailTransport->isChecked());

    auto mCheckDuplicateEmails = w.findChild<QCheckBox *>(u"checkduplicatedemailsaddresses"_s);
    QVERIFY(mCheckDuplicateEmails);
    QVERIFY(!mCheckDuplicateEmails->text().isEmpty());
    QVERIFY(!mCheckDuplicateEmails->isChecked());

    auto mCheckSendAttachments = w.findChild<QCheckBox *>(u"checksendattachment"_s);
    QVERIFY(mCheckSendAttachments);
    QVERIFY(!mCheckSendAttachments->text().isEmpty());
    QVERIFY(!mCheckSendAttachments->isChecked());
}

void CheckBeforeSendConfigureWidgetTest::shouldResetValue()
{
    CheckBeforeSendConfigureWidget w(nullptr);

    auto mCheckPlainTextMail = w.findChild<QCheckBox *>(u"checkplaintext"_s);
    auto mCheckMailTransport = w.findChild<QCheckBox *>(u"smtpdefinedinidentity"_s);
    auto mCheckDuplicateEmails = w.findChild<QCheckBox *>(u"checkduplicatedemailsaddresses"_s);
    auto mCheckSendAttachments = w.findChild<QCheckBox *>(u"checksendattachment"_s);

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
