/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkduplicateemailsdialogtest.h"
#include "../duplicateemails/checkduplicateemailsdialog.h"
#include <QDialogButtonBox>
#include <QLabel>
#include <QListWidget>
#include <QStandardPaths>
#include <QTest>

CheckDuplicateEmailsDialogTest::CheckDuplicateEmailsDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

CheckDuplicateEmailsDialogTest::~CheckDuplicateEmailsDialogTest() = default;

void CheckDuplicateEmailsDialogTest::shouldHaveDefaultValue()
{
    CheckDuplicateEmailsDialog dlg;
    auto mListWidget = dlg.findChild<QListWidget *>(QStringLiteral("listwidget"));
    QVERIFY(mListWidget);
    QCOMPARE(mListWidget->count(), 0);

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    auto lab = dlg.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());
}

void CheckDuplicateEmailsDialogTest::shouldAddEmails()
{
    CheckDuplicateEmailsDialog dlg;
    auto mListWidget = dlg.findChild<QListWidget *>(QStringLiteral("listwidget"));

    QMap<QString, int> map;
    map.insert(QStringLiteral("foo"), 5);
    map.insert(QStringLiteral("bla"), 5);
    map.insert(QStringLiteral("kde.org"), 7);
    map.insert(QStringLiteral("linux.fr"), 2);
    dlg.setDuplicatedEmails(map);

    QCOMPARE(mListWidget->count(), map.count());
}

QTEST_MAIN(CheckDuplicateEmailsDialogTest)
