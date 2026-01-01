/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownpreviewdialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "markdownpreviewdialog.h"
#include "markdownpreviewwidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

QTEST_MAIN(MarkdownPreviewDialogTest)

MarkdownPreviewDialogTest::MarkdownPreviewDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void MarkdownPreviewDialogTest::shouldHaveDefaultValue()
{
    MarkdownPreviewDialog dlg;
    auto mainLayout = dlg.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);

    auto mPreviewWidget = dlg.findChild<MarkdownPreviewWidget *>(u"previewwidget"_s);
    QVERIFY(mPreviewWidget);

    auto buttonBox = dlg.findChild<QDialogButtonBox *>(u"buttonbox"_s);
    QVERIFY(buttonBox);
}

#include "moc_markdownpreviewdialogtest.cpp"
