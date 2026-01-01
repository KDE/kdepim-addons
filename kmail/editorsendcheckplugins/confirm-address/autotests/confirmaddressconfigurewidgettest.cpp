/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfigurewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "../confirmaddressconfiguretab.h"
#include "../confirmaddressconfigurewidget.h"

#include <QCheckBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

ConfirmAddressConfigureWidgetTest::ConfirmAddressConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ConfirmAddressConfigureWidgetTest::~ConfirmAddressConfigureWidgetTest() = default;

void ConfirmAddressConfigureWidgetTest::shouldHaveDefaultValue()
{
    ConfirmAddressConfigureWidget w;

    auto vboxlayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(vboxlayout);

    auto mConfirmAddressConfigureTab = w.findChild<ConfirmAddressConfigureTab *>(u"confirmaddresstab"_s);
    QVERIFY(mConfirmAddressConfigureTab);
}

void ConfirmAddressConfigureWidgetTest::shouldLoadSaveResetValue()
{
    ConfirmAddressConfigureWidget w;
    w.loadSettings();
    w.saveSettings();
    w.resetSettings();
}

QTEST_MAIN(ConfirmAddressConfigureWidgetTest)

#include "moc_confirmaddressconfigurewidgettest.cpp"
