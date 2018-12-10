/*
  Copyright (c) 2016-2018 Montel Laurent <montel@kde.org>
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2013-2014  David Rosca <nowrep@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
* ============================================================ */
#ifndef ADBLOCKREGEXP_H
#define ADBLOCKREGEXP_H

#include <QRegularExpression>
#include <QStringList>

namespace AdBlock {
class AdblockRegExp : public QRegularExpression
{
public:
    AdblockRegExp();
    AdblockRegExp(const QString &pattern, Qt::CaseSensitivity cs = Qt::CaseSensitive);
    AdblockRegExp(const AdblockRegExp &re);

    void setMinimal(bool minimal);
    int indexIn(const QString &str, int offset = 0) const;
    int matchedLength() const;
    QString cap(int nth = 0) const;

private:
    QStringList m_capturedTexts;
    int m_matchedLength;
};
}
#endif
