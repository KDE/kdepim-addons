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
    Lunarphases();
    ~Lunarphases() override
    {
    }

    Element::List createDayElements(const QDate &) override;
    Element::List createWeekElements(const QDate &) override;

    QString info() const override;
};

class LunarphasesFactory : public DecorationFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.korganizer.Lunarphases")
public:
    Decoration *createPluginFactory() override
    {
        return new Lunarphases;
    }
};

