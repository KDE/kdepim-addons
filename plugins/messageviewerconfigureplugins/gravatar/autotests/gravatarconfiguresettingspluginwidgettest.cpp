/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gravatarconfiguresettingspluginwidgettest.h"
#include "../gravatarconfiguresettingspluginwidget.h"
#include <Gravatar/GravatarConfigureSettingsWidget>
#include <QCheckBox>
#include <QTest>
#include <QVBoxLayout>

QTEST_MAIN(GravatarConfigureSettingsPluginWidgetTest)

GravatarConfigureSettingsPluginWidgetTest::GravatarConfigureSettingsPluginWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void GravatarConfigureSettingsPluginWidgetTest::shouldHaveDefaultValue()
{
    GravatarConfigureSettingsPluginWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mEnableGravatarSupport = w.findChild<QCheckBox *>(QStringLiteral("gravatarcheckbox"));
    QVERIFY(mEnableGravatarSupport);
    QVERIFY(!mEnableGravatarSupport->isChecked());
    QVERIFY(!mEnableGravatarSupport->text().isEmpty());

    auto mGravatarConfigWidget = w.findChild<Gravatar::GravatarConfigureSettingsWidget *>(QStringLiteral("gravatarconfigwidget"));
    QVERIFY(mGravatarConfigWidget);
}

#include "moc_gravatarconfiguresettingspluginwidgettest.cpp"
