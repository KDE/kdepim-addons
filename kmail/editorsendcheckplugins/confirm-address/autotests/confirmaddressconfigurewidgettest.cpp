/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfigurewidgettest.h"
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

    auto vboxlayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(vboxlayout);

    auto mConfirmAddressConfigureTab = w.findChild<ConfirmAddressConfigureTab *>(QStringLiteral("confirmaddresstab"));
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
