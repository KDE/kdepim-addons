/*
    SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "markdowncreatelinkdialogtest.h"
#include "markdowncreatelinkdialog.h"
#include "markdowncreatelinkwidget.h"

#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(MarkdownCreateLinkDialogTest)

MarkdownCreateLinkDialogTest::MarkdownCreateLinkDialogTest(QObject *parent)
    : QObject(parent)
{
}

void MarkdownCreateLinkDialogTest::shouldHaveDefaultValue()
{
    MarkdownCreateLinkDialog dlg;
    QVERIFY(!dlg.windowTitle().isEmpty());
    auto mainLayout = dlg.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto mMarkdownCreateLinkWidget = dlg.findChild<MarkdownCreateLinkWidget *>(QStringLiteral("markdowncreatelinkwidget"));
    QVERIFY(mMarkdownCreateLinkWidget);
    auto box = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(box);
    QVERIFY(dlg.linkStr().isEmpty());
}
