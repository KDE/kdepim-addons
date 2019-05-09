/*
    Copyright (C) 2019 Laurent Montel <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
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
