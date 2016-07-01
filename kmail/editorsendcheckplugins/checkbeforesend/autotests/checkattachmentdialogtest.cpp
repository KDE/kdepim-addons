/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "checkattachmentdialogtest.h"
#include "../sendattachments/checkattachmentdialog.h"
#include <QDialogButtonBox>
#include <QLabel>
#include <QListWidget>
#include <QTest>

CheckAttachmentDialogTest::CheckAttachmentDialogTest(QObject *parent)
    : QObject(parent)
{

}

CheckAttachmentDialogTest::~CheckAttachmentDialogTest()
{

}

void CheckAttachmentDialogTest::shouldHaveDefaultValue()
{
    CheckAttachmentDialog w;
    QDialogButtonBox *buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    QLabel *lab =  w.findChild<QLabel *>(QStringLiteral("lab"));
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());

    QListWidget *mListWidget = w.findChild<QListWidget *>(QStringLiteral("listwidget"));
    QVERIFY(mListWidget);
    QCOMPARE(mListWidget->count(), 0);
}

void CheckAttachmentDialogTest::shouldAddEmails()
{
    CheckAttachmentDialog w;

    QListWidget *mListWidget = w.findChild<QListWidget *>(QStringLiteral("listwidget"));
    w.setEmails(QStringList() << QStringLiteral("a") << QStringLiteral("b") << QStringLiteral("v") );
    QCOMPARE(mListWidget->count(), 3);
}

QTEST_MAIN(CheckAttachmentDialogTest)
