/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertshorturlconfiguredialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "../insertshorturlconfiguredialog.h"
#include "../insertshorturlconfigurewidget.h"

#include <QDialogButtonBox>
#include <QTest>

QTEST_MAIN(InsertShorturlConfigureDialogTest)

InsertShorturlConfigureDialogTest::InsertShorturlConfigureDialogTest(QObject *parent)
    : QObject(parent)
{
}

void InsertShorturlConfigureDialogTest::shouldHaveDefaultValues()
{
    InsertShorturlConfigureDialog dlg;

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(u"buttonbox"_s);
    QVERIFY(buttonBox);

    auto mInsertShortUrlWidget = dlg.findChild<InsertShorturlConfigureWidget *>(u"insertshorturlwidget"_s);
    QVERIFY(mInsertShortUrlWidget);
}

#include "moc_insertshorturlconfiguredialogtest.cpp"
