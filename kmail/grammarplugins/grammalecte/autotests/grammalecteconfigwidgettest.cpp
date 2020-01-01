/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
