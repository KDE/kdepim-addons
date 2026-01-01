/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "scamconfiguresettingswidgettest.h"
#include "../scamconfiguresettingswidget.h"
#include <QHeaderView>
#include <QTest>
#include <QTreeWidget>
#include <QVBoxLayout>
QTEST_MAIN(ScamConfigureSettingsWidgetTest)
ScamConfigureSettingsWidgetTest::ScamConfigureSettingsWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void ScamConfigureSettingsWidgetTest::shouldHaveDefaultValues()
{
    ScamConfigureSettingsWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTreeWidget = w.findChild<QTreeWidget *>(QStringLiteral("mTreeWidget"));
    QVERIFY(mTreeWidget);
    QVERIFY(!mTreeWidget->rootIsDecorated());
    QVERIFY(!mTreeWidget->header()->sectionsMovable());
}

#include "moc_scamconfiguresettingswidgettest.cpp"
