/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "mailmergedialogtest.h"
#include "../mailmergedialog.h"
#include "../widgets/mailmergewidget.h"
#include <QDialogButtonBox>
#include <QTest>

MailMergeDialogTest::MailMergeDialogTest(QObject *parent)
    : QObject(parent)
{
}

MailMergeDialogTest::~MailMergeDialogTest()
{
}

void MailMergeDialogTest::shouldHaveDefaultValue()
{
    MailMerge::MailMergeDialog dlg;

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    auto mailMergeWidget = dlg.findChild<MailMerge::MailMergeWidget *>(QStringLiteral("mailmergewidget"));
    QVERIFY(mailMergeWidget);
}

QTEST_MAIN(MailMergeDialogTest)
