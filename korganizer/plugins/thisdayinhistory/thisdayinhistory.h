/*
  This file is part of KOrganizer.
  SPDX-FileCopyrightText: 2001 Cornelius Schumacher <schumacher@kde.org>
  SPDX-FileCopyrightText: 2007 Loïc Corbasson <loic.corbasson@gmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KORG_PLUGINS_THISDAYINHISTORY_THISDAYINHISTORY_H
#define KORG_PLUGINS_THISDAYINHISTORY_THISDAYINHISTORY_H

#include <EventViews/CalendarDecoration>

using namespace EventViews::CalendarDecoration;

class ThisDayInHistory : public Decoration
{
public:
    ThisDayInHistory();
    ~ThisDayInHistory() override
    {
    }

    Element::List createDayElements(const QDate &) override;
    Element::List createMonthElements(const QDate &) override;

    //    void configure( QWidget *parent );

    QString info() const override;
};

class ThisDayInHistoryFactory : public DecorationFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.korganizer.ThisDayInHistory")
public:
    Decoration *createPluginFactory() override
    {
        return new ThisDayInHistory;
    }
};

#endif
