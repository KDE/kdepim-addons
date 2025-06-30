/*
    SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "markdowncreatelinkdialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "markdowncreatelinkdialog.h"
#include "markdowncreatelinkwidget.h"

#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(MarkdownCreateLinkDialogTest)

MarkdownCreateLinkDialogTest::MarkdownCreateLinkDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void MarkdownCreateLinkDialogTest::shouldHaveDefaultValue()
{
    MarkdownCreateLinkDialog dlg;
    QVERIFY(!dlg.windowTitle().isEmpty());
    auto mainLayout = dlg.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);

    auto mMarkdownCreateLinkWidget = dlg.findChild<MarkdownCreateLinkWidget *>(u"markdowncreatelinkwidget"_s);
    QVERIFY(mMarkdownCreateLinkWidget);
    auto box = dlg.findChild<QDialogButtonBox *>(u"buttonbox"_s);
    QVERIFY(box);
    QVERIFY(dlg.linkStr().isEmpty());
}

#include "moc_markdowncreatelinkdialogtest.cpp"
