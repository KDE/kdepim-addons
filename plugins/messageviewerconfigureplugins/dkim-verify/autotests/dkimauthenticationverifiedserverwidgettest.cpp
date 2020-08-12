/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

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
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));


    DKIMAuthenticationVerifiedServerSelectorWidget *mSelector = w.findChild<DKIMAuthenticationVerifiedServerSelectorWidget *>(QStringLiteral("mSelector"));
    QVERIFY(mSelector);
}
