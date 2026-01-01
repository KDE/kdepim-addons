/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimauthenticationverifiedserverwidgettest.h"
#include "dkimauthenticationverifiedserverwidget.h"
#include <QTest>
#include <QVBoxLayout>

QTEST_MAIN(DKIMAuthenticationVerifiedServerWidgetTest)
DKIMAuthenticationVerifiedServerWidgetTest::DKIMAuthenticationVerifiedServerWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void DKIMAuthenticationVerifiedServerWidgetTest::shouldHaveDefaultValues()
{
    DKIMAuthenticationVerifiedServerWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mSelector = w.findChild<DKIMAuthenticationVerifiedServerSelectorWidget *>(QStringLiteral("mSelector"));
    QVERIFY(mSelector);
}

#include "moc_dkimauthenticationverifiedserverwidgettest.cpp"
