/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownconfigurewidgettest.h"
using namespace Qt::Literals::StringLiterals;

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
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mLatexSupport = w.findChild<QCheckBox *>(u"latex"_s);
    QVERIFY(mLatexSupport);
    QVERIFY(!mLatexSupport->text().isEmpty());

    auto mExtraDefinitionLists = w.findChild<QCheckBox *>(u"extradefinitionlists"_s);
    QVERIFY(mExtraDefinitionLists);
    QVERIFY(!mExtraDefinitionLists->text().isEmpty());
}

#include "moc_markdownconfigurewidgettest.cpp"
