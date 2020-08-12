/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownconfigurewidgettest.h"
#include "markdownconfigurewidget.h"
#include <QCheckBox>
#include <QTest>
#include <QVBoxLayout>

QTEST_MAIN(MarkdownConfigureWidgetTest)
MarkdownConfigureWidgetTest::MarkdownConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void MarkdownConfigureWidgetTest::shouldHaveDefaultValue()
{
    MarkdownConfigureWidget w;
    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins(0, 0, 0, 0));

    QCheckBox *mLatexSupport = w.findChild<QCheckBox *>(QStringLiteral("latex"));
    QVERIFY(mLatexSupport);
    QVERIFY(!mLatexSupport->text().isEmpty());

    QCheckBox *mExtraDefinitionLists = w.findChild<QCheckBox *>(QStringLiteral("extradefinitionlists"));
    QVERIFY(mExtraDefinitionLists);
    QVERIFY(!mExtraDefinitionLists->text().isEmpty());
}
