/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownpreviewdialogtest.h"
#include "markdownpreviewdialog.h"
#include "markdownpreviewwidget.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(MarkdownPreviewDialogTest)

MarkdownPreviewDialogTest::MarkdownPreviewDialogTest(QObject *parent)
    : QObject(parent)
{
}

void MarkdownPreviewDialogTest::shouldHaveDefaultValue()
{
    MarkdownPreviewDialog dlg;
    QVBoxLayout *mainLayout = dlg.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    MarkdownPreviewWidget *mPreviewWidget = dlg.findChild<MarkdownPreviewWidget *>(QStringLiteral("previewwidget"));
    QVERIFY(mPreviewWidget);

    QDialogButtonBox *buttonBox = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);
}
