/*
  This file is part of KAddressBook.
  SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDateTime>
#include <QString>

/**
  This class parses the datetime out of a given string with the
  help of a pattern.

  The pattern can contain the following place holders:
    y = year (e.g. 82)
    Y = year (e.g. 1982)
    m = month (e.g. 7, 07 or 12)
    M = month (e.g. 07 or 12)
    d = day (e.g. 3, 03 or 17)
    D = day (e.g. 03 or 17)
    H = hour (e.g. 12)
    I = minute (e.g. 56)
    S = second (e.g. 30)
 */
class DateParser
{
public:
    explicit DateParser(const QString &pattern);
    ~DateParser();

    QDateTime parse(const QString &dateStr) const;

private:
    QString mPattern;
};
