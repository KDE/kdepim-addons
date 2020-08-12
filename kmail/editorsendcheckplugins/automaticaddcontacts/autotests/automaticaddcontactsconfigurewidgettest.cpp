/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsconfigurewidgettest.h"
#include "../automaticaddcontactsconfigurewidget.h"
#include "../automaticaddcontactsconfiguretab.h"

#include <QTest>
#include <QVBoxLayout>
#include <QStandardPaths>

AutomaticAddContactsConfigureWidgetTest::AutomaticAddContactsConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

AutomaticAddContactsConfigureWidgetTest::~AutomaticAddContactsConfigureWidgetTest()
{
}

void AutomaticAddContactsConfigureWidgetTest::shouldHaveDefaultValue()
{
    AutomaticAddContactsConfigureWidget w(nullptr);

    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    AutomaticAddContactsConfigureTab *mConfigureTab = w.findChild<AutomaticAddContactsConfigureTab *>(QStringLiteral("configuretab"));
    QVERIFY(mConfigureTab);
}

QTEST_MAIN(AutomaticAddContactsConfigureWidgetTest)
