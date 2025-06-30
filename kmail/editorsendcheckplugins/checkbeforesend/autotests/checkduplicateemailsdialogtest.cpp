/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkduplicateemailsdialogtest.h"
using namespace Qt::Literals::StringLiterals;

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
    auto mListWidget = dlg.findChild<QListWidget *>(u"listwidget"_s);
    QVERIFY(mListWidget);
    QCOMPARE(mListWidget->count(), 0);

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(u"buttonbox"_s);
    QVERIFY(buttonBox);

    auto lab = dlg.findChild<QLabel *>(u"label"_s);
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());
}

void CheckDuplicateEmailsDialogTest::shouldAddEmails()
{
    CheckDuplicateEmailsDialog dlg;
    auto mListWidget = dlg.findChild<QListWidget *>(u"listwidget"_s);

    QMap<QString, int> map;
    map.insert(u"foo"_s, 5);
    map.insert(u"bla"_s, 5);
    map.insert(u"kde.org"_s, 7);
    map.insert(u"linux.fr"_s, 2);
    dlg.setDuplicatedEmails(map);

    QCOMPARE(mListWidget->count(), map.count());
}

QTEST_MAIN(CheckDuplicateEmailsDialogTest)

#include "moc_checkduplicateemailsdialogtest.cpp"
