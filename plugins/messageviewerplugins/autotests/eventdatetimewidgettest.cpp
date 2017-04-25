/*
   Copyright (C) 2014-2017 Montel Laurent <montel@kde.org>

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

#include "eventdatetimewidgettest.h"
#include "../createeventplugin/eventdatetimewidget.h"
#include <KDateComboBox>
#include <KTimeComboBox>
#include <qtest.h>
#include <QSignalSpy>

EventDateTimeWidgetTest::EventDateTimeWidgetTest(QObject *parent)
    : QObject(parent)
{
}

EventDateTimeWidgetTest::~EventDateTimeWidgetTest()
{
}

void EventDateTimeWidgetTest::shouldHaveDefaultValue()
{
    MessageViewer::EventDateTimeWidget edit;
    KDateComboBox *datecombobox = edit.findChild<KDateComboBox *>(QStringLiteral("eventdatecombobox"));
    QVERIFY(datecombobox);
    KTimeComboBox *timecombobox = edit.findChild<KTimeComboBox *>(QStringLiteral("eventtimecombobox"));
    QVERIFY(timecombobox);
}

void EventDateTimeWidgetTest::shouldSetDateTime()
{
    MessageViewer::EventDateTimeWidget edit;
    const QDateTime currentDateTime = QDateTime::currentDateTime();
    edit.setDateTime(currentDateTime);
    QCOMPARE(edit.dateTime().time().minute(), currentDateTime.time().minute());
    QCOMPARE(edit.dateTime().time().hour(), currentDateTime.time().hour());
}

void EventDateTimeWidgetTest::shouldEmitSignalWhenDateTimeChanged()
{
    MessageViewer::EventDateTimeWidget edit;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    edit.setDateTime(currentDateTime);

    QSignalSpy spy(&edit, SIGNAL(dateTimeChanged(QDateTime)));
    currentDateTime.setDate(currentDateTime.date().addDays(1));
    edit.setDateTime(currentDateTime);

    QCOMPARE(spy.count(), 1);
}

void EventDateTimeWidgetTest::shouldEmitSignalWhenJustTimeChanged()
{
    MessageViewer::EventDateTimeWidget edit;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    edit.setDateTime(currentDateTime);

    QSignalSpy spy(&edit, SIGNAL(dateTimeChanged(QDateTime)));
    QTime time = currentDateTime.time().addSecs(3600);
    edit.setTime(time);

    QCOMPARE(spy.count(), 1);
}

void EventDateTimeWidgetTest::shouldEmitSignalWhenJustDateChanged()
{
    MessageViewer::EventDateTimeWidget edit;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    edit.setDateTime(currentDateTime);

    QSignalSpy spy(&edit, SIGNAL(dateTimeChanged(QDateTime)));
    QDate date = currentDateTime.date().addDays(1);
    edit.setDate(date);

    QCOMPARE(spy.count(), 1);
}

void EventDateTimeWidgetTest::shouldNotEmitSignalWhenDateTimeWasNotChanged()
{
    MessageViewer::EventDateTimeWidget edit;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    edit.setDateTime(currentDateTime);

    QSignalSpy spy(&edit, SIGNAL(dateTimeChanged(QDateTime)));
    currentDateTime.setDate(currentDateTime.date().addDays(1));
    edit.setDateTime(currentDateTime);

    QCOMPARE(spy.count(), 1);
    edit.setDateTime(currentDateTime);

    //FIX ME
    //QCOMPARE(spy.count(), 2);
}

QTEST_MAIN(EventDateTimeWidgetTest)
