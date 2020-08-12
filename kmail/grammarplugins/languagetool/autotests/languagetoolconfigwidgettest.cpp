/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolconfigwidgettest.h"
#include "languagetoolconfigwidget.h"
#include "languagetoolcombobox.h"
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QTest>
#include <QVBoxLayout>
#include <QStandardPaths>
#include <QToolButton>
#include <qtestmouse.h>

QTEST_MAIN(LanguageToolConfigWidgetTest)
LanguageToolConfigWidgetTest::LanguageToolConfigWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void LanguageToolConfigWidgetTest::shouldHaveDefaultValue()
{
    LanguageToolConfigWidget w;
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    QCheckBox *mUseLocalInstance = w.findChild<QCheckBox *>(QStringLiteral("uselocalinstance"));
    QVERIFY(mUseLocalInstance);
    QVERIFY(!mUseLocalInstance->text().isEmpty());
    QVERIFY(!mUseLocalInstance->isChecked());

    QLabel *instancePathLabel = w.findChild<QLabel *>(QStringLiteral("instancepath"));
    QVERIFY(instancePathLabel);
    QVERIFY(!instancePathLabel->text().isEmpty());
    QVERIFY(!instancePathLabel->isEnabled());

    QLineEdit *mInstancePath = w.findChild<QLineEdit *>(QStringLiteral("instancepath"));
    QVERIFY(mInstancePath);
    //We load default value
    QVERIFY(!mInstancePath->text().isEmpty());
    QVERIFY(!mInstancePath->isEnabled());
    QVERIFY(mInstancePath->isClearButtonEnabled());

    QLabel *languageLabel = w.findChild<QLabel *>(QStringLiteral("languageLabel"));
    QVERIFY(languageLabel);
    QVERIFY(!languageLabel->text().isEmpty());

    LanguageToolComboBox *mLanguageToolCombobox = w.findChild<LanguageToolComboBox *>(QStringLiteral("languagecombobox"));
    QVERIFY(mLanguageToolCombobox);

    QToolButton *refreshButton = w.findChild<QToolButton *>(QStringLiteral("refreshbutton"));
    QVERIFY(refreshButton);
    QVERIFY(!refreshButton->icon().isNull());
}

void LanguageToolConfigWidgetTest::shouldUpdateWidgets()
{
    LanguageToolConfigWidget w;

    QCheckBox *mUseLocalInstance = w.findChild<QCheckBox *>(QStringLiteral("uselocalinstance"));

    QLabel *instancePathLabel = w.findChild<QLabel *>(QStringLiteral("instancepath"));

    QLineEdit *mInstancePath = w.findChild<QLineEdit *>(QStringLiteral("instancepath"));
    QTest::mouseClick(mUseLocalInstance, Qt::LeftButton);

    QVERIFY(mUseLocalInstance->isChecked());
    QVERIFY(mUseLocalInstance->isEnabled());
    QVERIFY(instancePathLabel->isEnabled());
    QVERIFY(mInstancePath->isEnabled());

    QTest::mouseClick(mUseLocalInstance, Qt::LeftButton);
    QVERIFY(!mUseLocalInstance->isChecked());
    QVERIFY(mUseLocalInstance->isEnabled());
    QVERIFY(!instancePathLabel->isEnabled());
    QVERIFY(!mInstancePath->isEnabled());
}
