/*
  SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

  This file originates from QupZilla - WebKit based browser
  SPDX-FileCopyrightText: 2013-2014 David Rosca <nowrep@gmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

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
    auto that = const_cast<AdblockRegExp *>(this);
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
        return {};
    }

    return m_capturedTexts.at(nth);
}
