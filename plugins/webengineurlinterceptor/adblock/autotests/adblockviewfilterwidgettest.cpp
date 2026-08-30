/*
   SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "adblockviewfilterwidgettest.h"
#include "adblockviewfilterwidget.h"
#include <QTest>
#include <QVBoxLayout>
#include <TextCustomEditor/RichTextBrowser>
using namespace Qt::Literals::StringLiterals;

QTEST_MAIN(AdblockViewFilterWidgetTest)
AdblockViewFilterWidgetTest::AdblockViewFilterWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AdblockViewFilterWidgetTest::shouldHaveDefaultValues()
{
    AdblockViewFilterWidget w;
    const auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    const auto mRichTextBrowser = w.findChild<TextCustomEditor::RichTextBrowser *>(u"mRichTextBrowser"_s);
    QVERIFY(mRichTextBrowser);
}

#include "moc_adblockviewfilterwidgettest.cpp"
