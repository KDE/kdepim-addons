/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

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

#ifndef GRAMMARERROR_H
#define GRAMMARERROR_H

#include <QColor>
#include <QString>
#include <QDebug>
#include <QJsonObject>
#include "grammarcommon_export.h"
class GRAMMARCOMMON_EXPORT GrammarError
{
public:
    GrammarError();
    virtual ~GrammarError();
    Q_REQUIRED_RESULT QColor color() const;
    void setColor(const QColor &color);

    Q_REQUIRED_RESULT QString error() const;
    void setError(const QString &error);

    Q_REQUIRED_RESULT int blockId() const;
    void setBlockId(int blockId);

    Q_REQUIRED_RESULT int start() const;
    void setStart(int start);

    Q_REQUIRED_RESULT int length() const;
    void setLength(int length);

    Q_REQUIRED_RESULT QStringList suggestions() const;
    void setSuggestions(const QStringList &suggestions);

    Q_REQUIRED_RESULT bool isValid() const;

    virtual void parse(const QJsonObject &obj, int blockindex);

    Q_REQUIRED_RESULT bool operator ==(const GrammarError &other) const;

    Q_REQUIRED_RESULT QString option() const;
    void setOption(const QString &option);

    Q_REQUIRED_RESULT QString rule() const;
    void setRule(const QString &rule);

    Q_REQUIRED_RESULT QString url() const;
    void setUrl(const QString &url);

protected:
    QStringList mSuggestions;
    QString mError;
    QString mOption;
    QString mRule;
    QString mUrl;
    QColor mColor;
    int mBlockId = -1;
    int mStart = -1;
    int mLength = -1;
};
Q_DECLARE_METATYPE(GrammarError)
Q_DECLARE_TYPEINFO(GrammarError, Q_MOVABLE_TYPE);
GRAMMARCOMMON_EXPORT QDebug operator <<(QDebug d, const GrammarError &t);
#endif // GRAMMARERROR_H
