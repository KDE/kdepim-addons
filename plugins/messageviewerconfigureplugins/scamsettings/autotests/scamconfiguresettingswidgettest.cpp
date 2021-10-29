/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "scamconfiguresettingswidgettest.h"
#include "../scamconfiguresettingswidget.h"
#include <QTest>
QTEST_MAIN(ScamConfigureSettingsWidgetTest)
ScamConfigureSettingsWidgetTest::ScamConfigureSettingsWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void ScamConfigureSettingsWidgetTest::shouldHaveDefaultValues()
{
    ScamConfigureSettingsWidget w;
    // TODO
}
