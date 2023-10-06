/*
   SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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
    [[nodiscard]] QDateTime dateTime() const;

    [[nodiscard]] QDate date() const;
    [[nodiscard]] QTime time() const;
    void setTime(QTime time);
    void setDate(QDate date);

Q_SIGNALS:
    void dateTimeChanged(const QDateTime &dateTime);

private:
    void slotDateTimeChanged();
    KDateComboBox *const mDateEdit;
    KTimeComboBox *const mTimeEdit;
};
}
