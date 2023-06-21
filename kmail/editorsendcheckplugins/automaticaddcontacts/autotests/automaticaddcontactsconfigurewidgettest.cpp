/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsconfigurewidgettest.h"
#include "../automaticaddcontactsconfiguretab.h"
#include "../automaticaddcontactsconfigurewidget.h"

#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

AutomaticAddContactsConfigureWidgetTest::AutomaticAddContactsConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

AutomaticAddContactsConfigureWidgetTest::~AutomaticAddContactsConfigureWidgetTest() = default;

void AutomaticAddContactsConfigureWidgetTest::shouldHaveDefaultValue()
{
    AutomaticAddContactsConfigureWidget w(nullptr);

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto mConfigureTab = w.findChild<AutomaticAddContactsConfigureTab *>(QStringLiteral("configuretab"));
    QVERIFY(mConfigureTab);
}

QTEST_MAIN(AutomaticAddContactsConfigureWidgetTest)

#include "moc_automaticaddcontactsconfigurewidgettest.cpp"
