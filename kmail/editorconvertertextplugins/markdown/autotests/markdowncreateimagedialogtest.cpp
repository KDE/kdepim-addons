/*
    SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "markdowncreateimagedialogtest.h"
#include "markdowncreateimagedialog.h"
#include "markdowncreateimagewidget.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(MarkdownCreateImageDialogTest)

MarkdownCreateImageDialogTest::MarkdownCreateImageDialogTest(QObject *parent)
    : QObject(parent)
{
}

void MarkdownCreateImageDialogTest::shouldHaveDefaultValue()
{
    MarkdownCreateImageDialog dlg;
    QVERIFY(!dlg.windowTitle().isEmpty());
    QVBoxLayout *mainLayout = dlg.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    MarkdownCreateImageWidget *mMarkdownCreateImageWidget = dlg.findChild<MarkdownCreateImageWidget *>(QStringLiteral("markdowncreateimagewidget"));
    QVERIFY(mMarkdownCreateImageWidget);
    QDialogButtonBox *box = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(box);
    QVERIFY(dlg.linkStr().isEmpty());

    QPushButton *mOkButton = box->button(QDialogButtonBox::Ok);
    QVERIFY(mOkButton);
    QVERIFY(!mOkButton->isEnabled());
}
