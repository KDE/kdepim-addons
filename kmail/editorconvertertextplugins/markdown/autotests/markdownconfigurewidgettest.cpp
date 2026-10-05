/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownconfigurewidgettest.h"

#include "markdownconfigurewidget.h"
#include <QCheckBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;

QTEST_MAIN(MarkdownConfigureWidgetTest)
MarkdownConfigureWidgetTest::MarkdownConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void MarkdownConfigureWidgetTest::shouldHaveDefaultValue()
{
    MarkdownConfigureWidget w;
    const auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    const auto mLatexSupport = w.findChild<QCheckBox *>(u"latex"_s);
    QVERIFY(mLatexSupport);
    QVERIFY(!mLatexSupport->text().isEmpty());

    const auto mExtraDefinitionLists = w.findChild<QCheckBox *>(u"extradefinitionlists"_s);
    QVERIFY(mExtraDefinitionLists);
    QVERIFY(!mExtraDefinitionLists->text().isEmpty());
}

#include "moc_markdownconfigurewidgettest.cpp"
