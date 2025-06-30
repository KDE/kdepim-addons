/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkattachmentdialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "../sendattachments/checkattachmentdialog.h"
#include <QDialogButtonBox>
#include <QLabel>
#include <QListWidget>
#include <QStandardPaths>
#include <QTest>

CheckAttachmentDialogTest::CheckAttachmentDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

CheckAttachmentDialogTest::~CheckAttachmentDialogTest() = default;

void CheckAttachmentDialogTest::shouldHaveDefaultValue()
{
    CheckAttachmentDialog w;
    auto buttonBox = w.findChild<QDialogButtonBox *>(u"buttonbox"_s);
    QVERIFY(buttonBox);

    auto lab = w.findChild<QLabel *>(u"lab"_s);
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());

    auto mListWidget = w.findChild<QListWidget *>(u"listwidget"_s);
    QVERIFY(mListWidget);
    QCOMPARE(mListWidget->count(), 0);
}

void CheckAttachmentDialogTest::shouldAddEmails()
{
    CheckAttachmentDialog w;

    auto mListWidget = w.findChild<QListWidget *>(u"listwidget"_s);
    w.setEmails(QStringList() << u"a"_s << u"b"_s << QStringLiteral("v"));
    QCOMPARE(mListWidget->count(), 3);
}

QTEST_MAIN(CheckAttachmentDialogTest)

#include "moc_checkattachmentdialogtest.cpp"
