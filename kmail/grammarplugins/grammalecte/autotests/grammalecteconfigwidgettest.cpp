/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

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
    QCOMPARE(mainLayout->margin(), 0);

    QTabWidget *mTab = w.findChild<QTabWidget *>(QStringLiteral("mTab"));
    QVERIFY(mTab);

    QWidget *generalWidget = mTab->findChild<QWidget *>(QStringLiteral("general"));
    QVERIFY(generalWidget);
    QFormLayout *lay = generalWidget->findChild<QFormLayout *>(QStringLiteral("generallayout"));
    QVERIFY(lay);


    KUrlRequester *mPythonPath = generalWidget->findChild<KUrlRequester *>(QStringLiteral("pythonpath"));
    QVERIFY(mPythonPath);
    QVERIFY(mPythonPath->text().isEmpty());

    KUrlRequester *mGrammalectePath = generalWidget->findChild<KUrlRequester *>(QStringLiteral("grammalectepath"));
    QVERIFY(mGrammalectePath);
    QVERIFY(mGrammalectePath->text().isEmpty());


#if 0

    return w;


    mStackedWidget = new QStackedWidget(this);
    mStackedWidget->setObjectName(QStringLiteral("stackedwidget"));

    mScrollArea = new QScrollArea(this);
    mScrollArea->setObjectName(QStringLiteral("scrollarea"));
    mScrollArea->setWidgetResizable(true);
    mGrammarTabWidget = new QWidget;
    mGrammarTabWidget->setObjectName(QStringLiteral("grammar"));
    QVBoxLayout *layout = new QVBoxLayout(mGrammarTabWidget);
    layout->setObjectName(QStringLiteral("grammartablayout"));
    mScrollArea->setWidget(mGrammarTabWidget);

    mStackedWidget->addWidget(mScrollArea);

    mReloadSettingsWidget = new QWidget;
    mReloadSettingsWidget->setObjectName(QStringLiteral("reloadwidget"));
    mStackedWidget->addWidget(mReloadSettingsWidget);
    QVBoxLayout *reloadSettingsLayout = new QVBoxLayout(mReloadSettingsWidget);
    reloadSettingsLayout->setObjectName(QStringLiteral("reloadSettingsLayout"));
    QHBoxLayout *horizontallayout = new QHBoxLayout;
    reloadSettingsLayout->addLayout(horizontallayout);
    QLabel *label = new QLabel(i18n("Reload Settings"), this);
    label->setObjectName(QStringLiteral("label"));
    horizontallayout->addWidget(label);

    QToolButton *buttonReloadSettings = new QToolButton(this);
    buttonReloadSettings->setIcon(QIcon::fromTheme(QStringLiteral("view-refresh")));
    buttonReloadSettings->setObjectName(QStringLiteral("buttonReloadSettings"));
    horizontallayout->addWidget(buttonReloadSettings);
    connect(buttonReloadSettings, &QToolButton::clicked, this, &GrammalecteConfigWidget::loadGrammarSettings);

    reloadSettingsLayout->addStretch(1);
    return mStackedWidget;
#endif

}
