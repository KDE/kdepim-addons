/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkattachmentdialogtest.h"
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
    auto buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    auto lab = w.findChild<QLabel *>(QStringLiteral("lab"));
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());

    auto mListWidget = w.findChild<QListWidget *>(QStringLiteral("listwidget"));
    QVERIFY(mListWidget);
    QCOMPARE(mListWidget->count(), 0);
}

void CheckAttachmentDialogTest::shouldAddEmails()
{
    CheckAttachmentDialog w;

    auto mListWidget = w.findChild<QListWidget *>(QStringLiteral("listwidget"));
    w.setEmails(QStringList() << QStringLiteral("a") << QStringLiteral("b") << QStringLiteral("v"));
    QCOMPARE(mListWidget->count(), 3);
}

QTEST_MAIN(CheckAttachmentDialogTest)
