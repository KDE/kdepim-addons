/*
   Copyright (C) 2015-2016 Montel Laurent <montel@kde.org>

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

#include "gravatarcreatewidgettest.h"
#include <qtest.h>
#include "../widgets/gravatarcreatewidget.h"
#include <QLabel>
#include <QPushButton>

GravatarCreateWidgetTest::GravatarCreateWidgetTest(QObject *parent)
    : QObject(parent)
{

}

GravatarCreateWidgetTest::~GravatarCreateWidgetTest()
{

}

void GravatarCreateWidgetTest::shouldHaveDefaultValue()
{
    KABGravatar::GravatarCreateWidget widget;
    QLabel *lab = widget.findChild<QLabel *>(QStringLiteral("emaillabel"));
    QVERIFY(lab);

    QLabel *emaillabel = widget.findChild<QLabel *>(QStringLiteral("email"));
    QVERIFY(emaillabel);

    QPushButton *searchGravatar = widget.findChild<QPushButton *>(QStringLiteral("search"));
    QVERIFY(searchGravatar);

    QLabel *resultGravatar = widget.findChild<QLabel *>(QStringLiteral("result"));
    QVERIFY(resultGravatar);
}

void GravatarCreateWidgetTest::shouldEnableDisableSearchButton()
{
    KABGravatar::GravatarCreateWidget widget;
    QPushButton *searchGravatar = widget.findChild<QPushButton *>(QStringLiteral("search"));
    QVERIFY(!searchGravatar->isEnabled());

    widget.setEmail(QStringLiteral("foo"));
    QVERIFY(searchGravatar->isEnabled());

    widget.setEmail(QString());
    QVERIFY(!searchGravatar->isEnabled());

    widget.setEmail(QStringLiteral("s"));
    QVERIFY(searchGravatar->isEnabled());

    widget.setEmail(QStringLiteral(" "));
    QVERIFY(!searchGravatar->isEnabled());
}

QTEST_MAIN(GravatarCreateWidgetTest)
