/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "mailmergedialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "../mailmergedialog.h"
#include "../widgets/mailmergewidget.h"
#include <QDialogButtonBox>
#include <QTest>

MailMergeDialogTest::MailMergeDialogTest(QObject *parent)
    : QObject(parent)
{
}

MailMergeDialogTest::~MailMergeDialogTest() = default;

void MailMergeDialogTest::shouldHaveDefaultValue()
{
    MailMerge::MailMergeDialog dlg;

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(u"buttonbox"_s);
    QVERIFY(buttonBox);

    auto mailMergeWidget = dlg.findChild<MailMerge::MailMergeWidget *>(u"mailmergewidget"_s);
    QVERIFY(mailMergeWidget);
}

QTEST_MAIN(MailMergeDialogTest)

#include "moc_mailmergedialogtest.cpp"
