/*
    SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "markdowncreateimagedialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "markdowncreateimagedialog.h"
#include "markdowncreateimagewidget.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(MarkdownCreateImageDialogTest)

MarkdownCreateImageDialogTest::MarkdownCreateImageDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void MarkdownCreateImageDialogTest::shouldHaveDefaultValue()
{
    MarkdownCreateImageDialog dlg;
    QVERIFY(!dlg.windowTitle().isEmpty());
    auto mainLayout = dlg.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);

    auto mMarkdownCreateImageWidget = dlg.findChild<MarkdownCreateImageWidget *>(u"markdowncreateimagewidget"_s);
    QVERIFY(mMarkdownCreateImageWidget);
    auto box = dlg.findChild<QDialogButtonBox *>(u"buttonbox"_s);
    QVERIFY(box);
    QVERIFY(dlg.linkStr().isEmpty());

    QPushButton *mOkButton = box->button(QDialogButtonBox::Ok);
    QVERIFY(mOkButton);
    QVERIFY(!mOkButton->isEnabled());
}

#include "moc_markdowncreateimagedialogtest.cpp"
