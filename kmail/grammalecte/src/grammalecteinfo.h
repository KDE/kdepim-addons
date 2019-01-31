/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef GRAMMALECTEINFO_H
#define GRAMMALECTEINFO_H

#include <QObject>
#include <QColor>
#include <QString>

class GrammalecteInfo
{
public:
    GrammalecteInfo();
    ~GrammalecteInfo();
    Q_REQUIRED_RESULT QColor color() const;
    void setColor(const QColor &color);

    Q_REQUIRED_RESULT QString error() const;
    void setError(const QString &error);

    Q_REQUIRED_RESULT int blockId() const;
    void setBlockId(int blockId);

    Q_REQUIRED_RESULT int begin() const;
    void setBegin(int begin);

    Q_REQUIRED_RESULT int end() const;
    void setEnd(int end);

    Q_REQUIRED_RESULT QStringList suggestions() const;
    void setSuggestions(const QStringList &suggestions);

private:
    QStringList mSuggestions;
    QString mError;
    QColor mColor;
    int mBlockId = -1;
    int mBegin = -1;
    int mEnd = -1;
};

Q_DECLARE_TYPEINFO(GrammalecteInfo, Q_MOVABLE_TYPE);

#endif // GRAMMALECTEINFO_H
