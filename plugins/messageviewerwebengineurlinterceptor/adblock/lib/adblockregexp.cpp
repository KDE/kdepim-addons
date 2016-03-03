/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2013-2014  David Rosca <nowrep@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
#include "adblockregexp.h"
#include "adblockutil.h"
using namespace AdBlock;

AdblockRegExp::AdblockRegExp()
    : QRegularExpression(QString(), QRegularExpression::DotMatchesEverythingOption)
    , m_matchedLength(-1)
{
}

AdblockRegExp::AdblockRegExp(const QString &pattern, Qt::CaseSensitivity cs)
    : QRegularExpression(pattern, QRegularExpression::DotMatchesEverythingOption)
    , m_matchedLength(-1)
{
    if (cs == Qt::CaseInsensitive) {
        setPatternOptions(patternOptions() | QRegularExpression::CaseInsensitiveOption);
    }
}

AdblockRegExp::AdblockRegExp(const AdblockRegExp &re)
    : QRegularExpression(re)
    , m_matchedLength(-1)
{
}

void AdblockRegExp::setMinimal(bool minimal)
{
    QRegularExpression::PatternOptions opt;

    if (minimal) {
        opt = patternOptions() | QRegularExpression::InvertedGreedinessOption;
    } else {
        opt = patternOptions() & ~QRegularExpression::InvertedGreedinessOption;
    }

    setPatternOptions(opt);
}

int AdblockRegExp::indexIn(const QString &str, int offset) const
{
    AdblockRegExp *that = const_cast<AdblockRegExp *>(this);
    QRegularExpressionMatch m = match(str, offset);

    if (!m.hasMatch()) {
        that->m_matchedLength = -1;
        that->m_capturedTexts.clear();
        return -1;
    }

    that->m_matchedLength = m.capturedLength();
    that->m_capturedTexts = m.capturedTexts();
    return m.capturedStart();
}

int AdblockRegExp::matchedLength() const
{
    return m_matchedLength;
}

QString AdblockRegExp::cap(int nth) const
{
    if (!AdblockUtil::containsIndex(m_capturedTexts, nth)) {
        return QString();
    }

    return m_capturedTexts.at(nth);
}

