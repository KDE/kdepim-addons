/*
   SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertshorturlconfiguredialogtest.h"
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

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    auto mInsertShortUrlWidget = dlg.findChild<InsertShorturlConfigureWidget *>(QStringLiteral("insertshorturlwidget"));
    QVERIFY(mInsertShortUrlWidget);
}

#include "moc_insertshorturlconfiguredialogtest.cpp"
