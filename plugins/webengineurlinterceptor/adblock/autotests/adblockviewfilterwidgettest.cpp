/*
   SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "adblockviewfilterwidgettest.h"
#include "adblockviewfilterwidget.h"
#include <QTest>
#include <QVBoxLayout>
#include <TextCustomEditor/RichTextBrowser>

QTEST_MAIN(AdblockViewFilterWidgetTest)
AdblockViewFilterWidgetTest::AdblockViewFilterWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AdblockViewFilterWidgetTest::shouldHaveDefaultValues()
{
    AdblockViewFilterWidget w;
    const auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    const auto mRichTextBrowser = w.findChild<TextCustomEditor::RichTextBrowser *>(QStringLiteral("mRichTextBrowser"));
    QVERIFY(mRichTextBrowser);
}

#include "moc_adblockviewfilterwidgettest.cpp"
