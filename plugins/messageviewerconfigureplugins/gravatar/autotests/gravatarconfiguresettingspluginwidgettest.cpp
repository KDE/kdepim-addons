/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gravatarconfiguresettingspluginwidgettest.h"
#include "../gravatarconfiguresettingspluginwidget.h"
#include <Gravatar/GravatarConfigureSettingsWidget>
#include <QCheckBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

QTEST_MAIN(GravatarConfigureSettingsPluginWidgetTest)

GravatarConfigureSettingsPluginWidgetTest::GravatarConfigureSettingsPluginWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void GravatarConfigureSettingsPluginWidgetTest::shouldHaveDefaultValue()
{
    GravatarConfigureSettingsPluginWidget w;

    const auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    const auto mEnableGravatarSupport = w.findChild<QCheckBox *>(u"gravatarcheckbox"_s);
    QVERIFY(mEnableGravatarSupport);
    QVERIFY(!mEnableGravatarSupport->isChecked());
    QVERIFY(!mEnableGravatarSupport->text().isEmpty());

    const auto mGravatarConfigWidget = w.findChild<Gravatar::GravatarConfigureSettingsWidget *>(u"gravatarconfigwidget"_s);
    QVERIFY(mGravatarConfigWidget);
}

#include "moc_gravatarconfiguresettingspluginwidgettest.cpp"
