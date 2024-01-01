/*
   SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "eventdatetimewidgettest.h"
#include "../createeventplugin/eventdatetimewidget.h"
#include <KDateComboBox>
#include <KTimeComboBox>
#include <QSignalSpy>
#include <QTest>

EventDateTimeWidgetTest::EventDateTimeWidgetTest(QObject *parent)
    : QObject(parent)
{
}

EventDateTimeWidgetTest::~EventDateTimeWidgetTest() = default;

void EventDateTimeWidgetTest::shouldHaveDefaultValue()
{
    MessageViewer::EventDateTimeWidget edit;
    auto datecombobox = edit.findChild<KDateComboBox *>(QStringLiteral("eventdatecombobox"));
    QVERIFY(datecombobox);
    auto timecombobox = edit.findChild<KTimeComboBox *>(QStringLiteral("eventtimecombobox"));
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

    QSignalSpy spy(&edit, &MessageViewer::EventDateTimeWidget::dateTimeChanged);
    currentDateTime.setDate(currentDateTime.date().addDays(1));
    edit.setDateTime(currentDateTime);

    QCOMPARE(spy.count(), 1);
}

void EventDateTimeWidgetTest::shouldEmitSignalWhenJustTimeChanged()
{
    MessageViewer::EventDateTimeWidget edit;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    edit.setDateTime(currentDateTime);

    QSignalSpy spy(&edit, &MessageViewer::EventDateTimeWidget::dateTimeChanged);
    QTime time = currentDateTime.time().addSecs(3600);
    edit.setTime(time);

    QCOMPARE(spy.count(), 1);
}

void EventDateTimeWidgetTest::shouldEmitSignalWhenJustDateChanged()
{
    MessageViewer::EventDateTimeWidget edit;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    edit.setDateTime(currentDateTime);

    QSignalSpy spy(&edit, &MessageViewer::EventDateTimeWidget::dateTimeChanged);
    QDate date = currentDateTime.date().addDays(1);
    edit.setDate(date);

    QCOMPARE(spy.count(), 1);
}

void EventDateTimeWidgetTest::shouldNotEmitSignalWhenDateTimeWasNotChanged()
{
    MessageViewer::EventDateTimeWidget edit;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    edit.setDateTime(currentDateTime);

    QSignalSpy spy(&edit, &MessageViewer::EventDateTimeWidget::dateTimeChanged);
    currentDateTime.setDate(currentDateTime.date().addDays(1));
    edit.setDateTime(currentDateTime);

    QCOMPARE(spy.count(), 1);
    edit.setDateTime(currentDateTime);

    // FIX ME
    // QCOMPARE(spy.count(), 2);
}

QTEST_MAIN(EventDateTimeWidgetTest)

#include "moc_eventdatetimewidgettest.cpp"
