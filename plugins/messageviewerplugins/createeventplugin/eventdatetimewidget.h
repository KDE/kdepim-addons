/*
   SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef EVENTDATETIMEWIDGET_H
#define EVENTDATETIMEWIDGET_H

#include <QDateTime>
#include <QWidget>
class KTimeComboBox;
class KDateComboBox;
namespace MessageViewer
{
class EventDateTimeWidgetPrivate;
class EventDateTimeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EventDateTimeWidget(QWidget *parent = nullptr);
    ~EventDateTimeWidget() override;

    void setMinimumDateTime(const QDateTime &dateTime);
    void setDateTime(const QDateTime &dateTime);
    QDateTime dateTime() const;

    QDate date() const;
    QTime time() const;
    void setTime(QTime time);
    void setDate(QDate date);

Q_SIGNALS:
    void dateTimeChanged(const QDateTime &dateTime);

private:
    void slotDateTimeChanged();
    KDateComboBox *mDateEdit = nullptr;
    KTimeComboBox *mTimeEdit = nullptr;
};
}

#endif // EVENTDATETIMEWIDGET_H
