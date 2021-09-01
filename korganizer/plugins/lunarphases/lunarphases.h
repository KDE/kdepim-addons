/*
  SPDX-FileCopyrightText: 2018 Allen Winter <winter@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <EventViews/CalendarDecoration>

using namespace EventViews::CalendarDecoration;

class Lunarphases : public Decoration
{
public:
    Lunarphases(QObject *parent = nullptr, const QVariantList &args = {});

    Q_REQUIRED_RESULT Element::List createDayElements(const QDate &) override;
    Q_REQUIRED_RESULT Element::List createWeekElements(const QDate &) override;

    Q_REQUIRED_RESULT QString info() const override;
};
