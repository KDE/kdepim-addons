/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfigurewidgettest.h"
#include "../confirmaddressconfigurewidget.h"
#include "../confirmaddressconfiguretab.h"

#include <QTest>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QStandardPaths>

ConfirmAddressConfigureWidgetTest::ConfirmAddressConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ConfirmAddressConfigureWidgetTest::~ConfirmAddressConfigureWidgetTest()
{
}

void ConfirmAddressConfigureWidgetTest::shouldHaveDefaultValue()
{
    ConfirmAddressConfigureWidget w;

    auto *vboxlayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(vboxlayout);

    auto *mConfirmAddressConfigureTab = w.findChild<ConfirmAddressConfigureTab *>(QStringLiteral("confirmaddresstab"));
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
