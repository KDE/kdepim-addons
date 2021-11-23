/*
  This file is part of KAddressBook.
  SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "dateparser.h"

DateParser::DateParser(const QString &pattern)
    : mPattern(pattern)
{
}

DateParser::~DateParser() = default;

QDateTime DateParser::parse(const QString &dateStr) const
{
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;

    int currPos = 0;
    for (int i = 0; i < mPattern.length(); ++i) {
        if (mPattern[i] == QLatin1Char('y')) { // 19YY
            if (currPos + 1 < dateStr.length()) {
                year = 1900 + QStringView(dateStr).mid(currPos, 2).toInt();

                currPos += 2;
            } else {
                return {};
            }
        } else if (mPattern[i] == QLatin1Char('Y')) { // YYYY
            if (currPos + 3 < dateStr.length()) {
                year = QStringView(dateStr).mid(currPos, 4).toInt();
                currPos += 4;
            } else {
                return {};
            }
        } else if (mPattern[i] == QLatin1Char('m')) { // M or MM
            if (currPos + 1 < dateStr.length()) {
                if (dateStr[currPos].isDigit()) {
                    if (dateStr[currPos + 1].isDigit()) {
                        month = QStringView(dateStr).mid(currPos, 2).toInt();

                        currPos += 2;
                        continue;
                    }
                }
            }
            if (currPos < dateStr.length()) {
                if (dateStr[currPos].isDigit()) {
                    month = QStringView(dateStr).mid(currPos, 1).toInt();

                    currPos++;
                    continue;
                }
            }

            return {};
        } else if (mPattern[i] == QLatin1Char('M')) { // 0M or MM
            if (currPos + 1 < dateStr.length()) {
                month = QStringView(dateStr).mid(currPos, 2).toInt();
                currPos += 2;
            } else {
                return {};
            }
        } else if (mPattern[i] == QLatin1Char('d')) { // D or DD
            if (currPos + 1 < dateStr.length()) {
                if (dateStr[currPos].isDigit()) {
                    if (dateStr[currPos + 1].isDigit()) {
                        day = QStringView(dateStr).mid(currPos, 2).toInt();
                        currPos += 2;
                        continue;
                    }
                }
            }
            if (currPos < dateStr.length()) {
                if (dateStr[currPos].isDigit()) {
                    day = QStringView(dateStr).mid(currPos, 1).toInt();
                    currPos++;
                    continue;
                }
            }

            return {};
        } else if (mPattern[i] == QLatin1Char('D')) { // 0D or DD
            if (currPos + 1 < dateStr.length()) {
                day = QStringView(dateStr).mid(currPos, 2).toInt();
                currPos += 2;
            } else {
                return {};
            }
        } else if (mPattern[i] == QLatin1Char('H')) { // 0H or HH
            if (currPos + 1 < dateStr.length()) {
                hour = QStringView(dateStr).mid(currPos, 2).toInt();
                currPos += 2;
            } else {
                return {};
            }
        } else if (mPattern[i] == QLatin1Char('I')) { // 0I or II
            if (currPos + 1 < dateStr.length()) {
                minute = QStringView(dateStr).mid(currPos, 2).toInt();
                currPos += 2;
            } else {
                return {};
            }
        } else if (mPattern[i] == QLatin1Char('S')) { // 0S or SS
            if (currPos + 1 < dateStr.length()) {
                second = QStringView(dateStr).mid(currPos, 2).toInt();
                currPos += 2;
            } else {
                return {};
            }
        } else {
            currPos++;
        }
    }

    return QDateTime(QDate(year, month, day), QTime(hour, minute, second));
}
