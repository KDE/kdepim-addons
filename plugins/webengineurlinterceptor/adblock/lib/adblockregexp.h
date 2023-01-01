/*
  SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

  This file originates from QupZilla - WebKit based browser
  SPDX-FileCopyrightText: 2013-2014 David Rosca <nowrep@gmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QRegularExpression>
#include <QStringList>

namespace AdBlock
{
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
