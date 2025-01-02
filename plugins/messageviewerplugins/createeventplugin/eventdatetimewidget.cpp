/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "eventdatetimewidget.h"
#include <KDateComboBox>
#include <KTimeComboBox>
#include <QHBoxLayout>

using namespace MessageViewer;

EventDateTimeWidget::EventDateTimeWidget(QWidget *parent)
    : QWidget(parent)
    , mDateEdit(new KDateComboBox(this))
    , mTimeEdit(new KTimeComboBox(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins({});
    mDateEdit->setObjectName(QLatin1StringView("eventdatecombobox"));
    mainLayout->addWidget(mDateEdit);
    mTimeEdit->setObjectName(QLatin1StringView("eventtimecombobox"));
    mainLayout->addWidget(mTimeEdit);
    const QDateTime currentDateTime = QDateTime::currentDateTime();
    setDateTime(currentDateTime);
    connect(mDateEdit, &KDateComboBox::dateChanged, this, &EventDateTimeWidget::slotDateTimeChanged);
    connect(mTimeEdit, &KTimeComboBox::timeChanged, this, &EventDateTimeWidget::slotDateTimeChanged);
    connect(mDateEdit, &KDateComboBox::dateEdited, this, &EventDateTimeWidget::slotDateTimeChanged);
    connect(mTimeEdit, &KTimeComboBox::timeEdited, this, &EventDateTimeWidget::slotDateTimeChanged);
}

EventDateTimeWidget::~EventDateTimeWidget() = default;

void EventDateTimeWidget::slotDateTimeChanged()
{
    Q_EMIT dateTimeChanged(dateTime());
}

void EventDateTimeWidget::setMinimumDateTime(const QDateTime &dtime)
{
    if (dateTime() != dtime) {
        mDateEdit->setMinimumDate(dtime.date());
        mTimeEdit->setMinimumTime(dtime.time());
    }
}

void EventDateTimeWidget::setDateTime(const QDateTime &dTime)
{
    if (dateTime() != dTime) {
        blockSignals(true);
        mDateEdit->setDate(dTime.date());
        mTimeEdit->setTime(dTime.time());
        blockSignals(false);
        slotDateTimeChanged();
    }
}

QDateTime EventDateTimeWidget::dateTime() const
{
    QDateTime dateTime = QDateTime::currentDateTime();
    dateTime.setTime(mTimeEdit->time());
    dateTime.setDate(mDateEdit->date());
    return dateTime;
}

QDate EventDateTimeWidget::date() const
{
    return mDateEdit->date();
}

QTime EventDateTimeWidget::time() const
{
    return mTimeEdit->time();
}

void EventDateTimeWidget::setTime(QTime time)
{
    mTimeEdit->setTime(time);
}

void EventDateTimeWidget::setDate(QDate date)
{
    mDateEdit->setDate(date);
}

#include "moc_eventdatetimewidget.cpp"
