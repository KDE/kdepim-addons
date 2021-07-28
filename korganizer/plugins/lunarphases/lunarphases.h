/*
  SPDX-FileCopyrightText: 2018 Allen Winter <winter@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <EventViews/CalendarDecoration>
#include <KHolidays/LunarPhase>
#include <QIcon>

using namespace EventViews::CalendarDecoration;

class Lunarphases : public Decoration
{
public:
    Lunarphases(QObject *parent = nullptr, const QVariantList &args = {});

    Q_REQUIRED_RESULT Element::List createDayElements(const QDate &) override;

    Q_REQUIRED_RESULT QString info() const override;
};

class LunarphasesElement : public Element
{
    Q_OBJECT
public:
    explicit LunarphasesElement(KHolidays::LunarPhase::Phase phase);

    Q_REQUIRED_RESULT QString shortText() const override;
    Q_REQUIRED_RESULT QString longText() const override;
    Q_REQUIRED_RESULT QPixmap newPixmap(const QSize &size) override;

private:
    QString mName;
    QIcon mIcon;
};
