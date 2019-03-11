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
    QVBoxLayout *mainLayout = dlg.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    MarkdownCreateLinkWidget *mMarkdownCreateLinkWidget = dlg.findChild<MarkdownCreateLinkWidget *>(QStringLiteral("markdowncreatelinkwidget"));
    QVERIFY(mMarkdownCreateLinkWidget);
    QDialogButtonBox *box = dlg.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(box);
    QVERIFY(dlg.linkStr().isEmpty());
}
