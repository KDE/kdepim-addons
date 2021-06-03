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

DateParser::~DateParser()
{
}

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
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 2)
                year = 1900 + QStringView(dateStr).mid(currPos, 2).toInt();
#else
                year = 1900 + dateStr.midRef(currPos, 2).toInt();
#endif

                currPos += 2;
            } else {
                return QDateTime();
            }
        } else if (mPattern[i] == QLatin1Char('Y')) { // YYYY
            if (currPos + 3 < dateStr.length()) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 2)
                year = QStringView(dateStr).mid(currPos, 4).toInt();
#else
                year = dateStr.midRef(currPos, 4).toInt();
#endif
                currPos += 4;
            } else {
                return QDateTime();
            }
        } else if (mPattern[i] == QLatin1Char('m')) { // M or MM
            if (currPos + 1 < dateStr.length()) {
                if (dateStr[currPos].isDigit()) {
                    if (dateStr[currPos + 1].isDigit()) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 2)
                        month = QStringView(dateStr).mid(currPos, 2).toInt();
#else
                        month = dateStr.midRef(currPos, 2).toInt();
#endif

                        currPos += 2;
                        continue;
                    }
                }
            }
            if (currPos < dateStr.length()) {
                if (dateStr[currPos].isDigit()) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 2)
                    month = QStringView(dateStr).mid(currPos, 1).toInt();
#else
                    month = dateStr.midRef(currPos, 1).toInt();
#endif

                    currPos++;
                    continue;
                }
            }

            return QDateTime();
        } else if (mPattern[i] == QLatin1Char('M')) { // 0M or MM
            if (currPos + 1 < dateStr.length()) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 2)
                month = QStringView(dateStr).mid(currPos, 2).toInt();
#else
                month = dateStr.midRef(currPos, 2).toInt();
#endif

                currPos += 2;
            } else {
                return QDateTime();
            }
        } else if (mPattern[i] == QLatin1Char('d')) { // D or DD
            if (currPos + 1 < dateStr.length()) {
                if (dateStr[currPos].isDigit()) {
                    if (dateStr[currPos + 1].isDigit()) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 2)
                        day = QStringView(dateStr).mid(currPos, 2).toInt();
#else
                        day = dateStr.midRef(currPos, 2).toInt();
#endif

                        currPos += 2;
                        continue;
                    }
                }
            }
            if (currPos < dateStr.length()) {
                if (dateStr[currPos].isDigit()) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 2)
                    day = QStringView(dateStr).mid(currPos, 1).toInt();
#else
                    day = dateStr.midRef(currPos, 1).toInt();
#endif

                    currPos++;
                    continue;
                }
            }

            return QDateTime();
        } else if (mPattern[i] == QLatin1Char('D')) { // 0D or DD
            if (currPos + 1 < dateStr.length()) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 2)
                day = QStringView(dateStr).mid(currPos, 2).toInt();
#else
                day = dateStr.midRef(currPos, 2).toInt();
#endif

                currPos += 2;
            } else {
                return QDateTime();
            }
        } else if (mPattern[i] == QLatin1Char('H')) { // 0H or HH
            if (currPos + 1 < dateStr.length()) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 2)
                hour = QStringView(dateStr).mid(currPos, 2).toInt();
#else
                hour = dateStr.midRef(currPos, 2).toInt();
#endif

                currPos += 2;
            } else {
                return QDateTime();
            }
        } else if (mPattern[i] == QLatin1Char('I')) { // 0I or II
            if (currPos + 1 < dateStr.length()) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 2)
                minute = QStringView(dateStr).mid(currPos, 2).toInt();
#else
                minute = dateStr.midRef(currPos, 2).toInt();
#endif

                currPos += 2;
            } else {
                return QDateTime();
            }
        } else if (mPattern[i] == QLatin1Char('S')) { // 0S or SS
            if (currPos + 1 < dateStr.length()) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 2)
                second = QStringView(dateStr).mid(currPos, 2).toInt();
#else
                second = dateStr.midRef(currPos, 2).toInt();
#endif

                currPos += 2;
            } else {
                return QDateTime();
            }
        } else {
            currPos++;
        }
    }

    return QDateTime(QDate(year, month, day), QTime(hour, minute, second));
}
