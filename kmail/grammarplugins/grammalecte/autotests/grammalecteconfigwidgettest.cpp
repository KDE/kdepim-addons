/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteconfigwidgettest.h"
#include "grammalecteconfigwidget.h"
#include <QTabWidget>
#include <QTest>
#include <QVBoxLayout>
#include <QStandardPaths>
#include <QFormLayout>
#include <KUrlRequester>
#include <QStackedWidget>
#include <QScrollArea>
#include <QLabel>
#include <QToolButton>
QTEST_MAIN(GrammalecteConfigWidgetTest)
GrammalecteConfigWidgetTest::GrammalecteConfigWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void GrammalecteConfigWidgetTest::shouldHaveDefaultValue()
{
    GrammalecteConfigWidget w(nullptr, true);
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    QTabWidget *mTab = w.findChild<QTabWidget *>(QStringLiteral("mTab"));
    QVERIFY(mTab);

    QWidget *generalWidget = mTab->findChild<QWidget *>(QStringLiteral("general"));
    QVERIFY(generalWidget);
    QFormLayout *lay = generalWidget->findChild<QFormLayout *>(QStringLiteral("generallayout"));
    QVERIFY(lay);

    KUrlRequester *mPythonPath = generalWidget->findChild<KUrlRequester *>(QStringLiteral("pythonpath"));
    QVERIFY(mPythonPath);
    QVERIFY(!mPythonPath->text().isEmpty());

    KUrlRequester *mGrammalectePath = generalWidget->findChild<KUrlRequester *>(QStringLiteral("grammalectepath"));
    QVERIFY(mGrammalectePath);
    QVERIFY(mGrammalectePath->text().isEmpty());

    QStackedWidget *mStackedWidget = mTab->findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QVERIFY(mStackedWidget);
    QScrollArea *mScrollArea = mStackedWidget->findChild<QScrollArea *>(QStringLiteral("scrollarea"));
    QVERIFY(mScrollArea);
    QVERIFY(mScrollArea->widget());
    QCOMPARE(mScrollArea->widget()->objectName(), QStringLiteral("grammar"));

    QWidget *mReloadSettingsWidget = mStackedWidget->findChild<QWidget *>(QStringLiteral("reloadwidget"));
    QVERIFY(mReloadSettingsWidget);

    QVBoxLayout *reloadSettingsLayout = mReloadSettingsWidget->findChild<QVBoxLayout *>(QStringLiteral("reloadSettingsLayout"));
    QVERIFY(reloadSettingsLayout);

    QLabel *label = mReloadSettingsWidget->findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());
    QToolButton *buttonReloadSettings = mReloadSettingsWidget->findChild<QToolButton *>(QStringLiteral("buttonReloadSettings"));
    QVERIFY(buttonReloadSettings);
    QVERIFY(!buttonReloadSettings->icon().isNull());
}
