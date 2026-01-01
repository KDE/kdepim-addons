/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsconfigurewidgettest.h"
using namespace Qt::Literals::StringLiterals;

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

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);

    auto mConfigureTab = w.findChild<AutomaticAddContactsConfigureTab *>(u"configuretab"_s);
    QVERIFY(mConfigureTab);
}

QTEST_MAIN(AutomaticAddContactsConfigureWidgetTest)

#include "moc_automaticaddcontactsconfigurewidgettest.cpp"
