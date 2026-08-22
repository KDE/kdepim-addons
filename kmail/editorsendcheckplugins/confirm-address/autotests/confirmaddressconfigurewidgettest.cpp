/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressconfigurewidgettest.h"

#include "../confirmaddressconfiguretab.h"
#include "../confirmaddressconfigurewidget.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <QCheckBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
ConfirmAddressConfigureWidgetTest::ConfirmAddressConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

ConfirmAddressConfigureWidgetTest::~ConfirmAddressConfigureWidgetTest() = default;

void ConfirmAddressConfigureWidgetTest::shouldHaveDefaultValue()
{
    const ConfirmAddressConfigureWidget w;

    const auto vboxlayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(vboxlayout);

    const auto mConfirmAddressConfigureTab = w.findChild<ConfirmAddressConfigureTab *>(u"confirmaddresstab"_s);
    QVERIFY(mConfirmAddressConfigureTab);
}

void ConfirmAddressConfigureWidgetTest::shouldLoadSaveResetValue()
{
    ConfirmAddressConfigureWidget w;
    w.loadSettings();
    w.saveSettings();
    w.resetSettings();
}

void ConfirmAddressConfigureWidgetTest::shouldRemoveSettingsFromUnknownIdentity()
{
    // 4242 is not a known identity uoid, so saving must drop its leftover settings.
    const QString staleGroupName = u"Confirm Address 4242"_s;
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup grp(config, u"Confirm Address"_s);
    KConfigGroup staleGroup = grp.group(staleGroupName);
    staleGroup.writeEntry("Domains", QStringList() << u"foo.com"_s);
    staleGroup.sync();
    QVERIFY(grp.groupList().contains(staleGroupName));

    ConfirmAddressConfigureWidget w;
    w.saveSettings();

    QVERIFY(!grp.groupList().contains(staleGroupName));
}

QTEST_MAIN(ConfirmAddressConfigureWidgetTest)

#include "moc_confirmaddressconfigurewidgettest.cpp"
