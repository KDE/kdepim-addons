/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteconfigwidgettest.h"
#include "grammalecteconfigwidget.h"
#include <KUrlRequester>
#include <QFormLayout>
#include <QLabel>
#include <QScrollArea>
#include <QStackedWidget>
#include <QStandardPaths>
#include <QTabWidget>
#include <QTest>
#include <QToolButton>
#include <QVBoxLayout>
QTEST_MAIN(GrammalecteConfigWidgetTest)
GrammalecteConfigWidgetTest::GrammalecteConfigWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void GrammalecteConfigWidgetTest::shouldHaveDefaultValue()
{
    GrammalecteConfigWidget w(nullptr, true);
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mTab = w.findChild<QTabWidget *>(QStringLiteral("mTab"));
    QVERIFY(mTab);

    auto generalWidget = mTab->findChild<QWidget *>(QStringLiteral("general"));
    QVERIFY(generalWidget);
    auto lay = generalWidget->findChild<QFormLayout *>(QStringLiteral("generallayout"));
    QVERIFY(lay);

    auto mPythonPath = generalWidget->findChild<KUrlRequester *>(QStringLiteral("pythonpath"));
    QVERIFY(mPythonPath);
    QVERIFY(!mPythonPath->text().isEmpty());

    auto mGrammalectePath = generalWidget->findChild<KUrlRequester *>(QStringLiteral("grammalectepath"));
    QVERIFY(mGrammalectePath);
    QVERIFY(mGrammalectePath->text().isEmpty());

    auto mStackedWidget = mTab->findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QVERIFY(mStackedWidget);
    auto mScrollArea = mStackedWidget->findChild<QScrollArea *>(QStringLiteral("scrollarea"));
    QVERIFY(mScrollArea);
    QVERIFY(mScrollArea->widget());
    QCOMPARE(mScrollArea->widget()->objectName(), QStringLiteral("grammar"));

    auto mReloadSettingsWidget = mStackedWidget->findChild<QWidget *>(QStringLiteral("reloadwidget"));
    QVERIFY(mReloadSettingsWidget);

    auto reloadSettingsLayout = mReloadSettingsWidget->findChild<QVBoxLayout *>(QStringLiteral("reloadSettingsLayout"));
    QVERIFY(reloadSettingsLayout);

    auto label = mReloadSettingsWidget->findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());
    auto buttonReloadSettings = mReloadSettingsWidget->findChild<QToolButton *>(QStringLiteral("buttonReloadSettings"));
    QVERIFY(buttonReloadSettings);
    QVERIFY(!buttonReloadSettings->icon().isNull());
}
