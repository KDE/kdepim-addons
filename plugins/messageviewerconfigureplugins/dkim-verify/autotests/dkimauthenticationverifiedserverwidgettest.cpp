/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimauthenticationverifiedserverwidgettest.h"
#include "dkimauthenticationverifiedserverwidget.h"
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

QTEST_MAIN(DKIMAuthenticationVerifiedServerWidgetTest)
DKIMAuthenticationVerifiedServerWidgetTest::DKIMAuthenticationVerifiedServerWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void DKIMAuthenticationVerifiedServerWidgetTest::shouldHaveDefaultValues()
{
    DKIMAuthenticationVerifiedServerWidget w;
    const auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    const auto mSelector = w.findChild<DKIMAuthenticationVerifiedServerSelectorWidget *>(u"mSelector"_s);
    QVERIFY(mSelector);
}

#include "moc_dkimauthenticationverifiedserverwidgettest.cpp"
