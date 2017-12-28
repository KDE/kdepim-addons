/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

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

#include "insertshorturlconfigurewidgettest.h"
#include "../insertshorturlconfigurewidget.h"

#include <QComboBox>
#include <QLabel>
#include <QTest>
#include <QVBoxLayout>

QTEST_MAIN(InsertShorturlConfigureWidgetTest)

InsertShorturlConfigureWidgetTest::InsertShorturlConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void InsertShorturlConfigureWidgetTest::shouldHaveDefaultValues()
{
    InsertShorturlConfigureWidget w;

    QVBoxLayout *mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->margin(), 0);

    QLabel *lab = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());

    QComboBox *mShortUrlServer = w.findChild<QComboBox *>(QStringLiteral("shorturlserver"));
    QVERIFY(mShortUrlServer);
}
