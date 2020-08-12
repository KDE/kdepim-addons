/*
  SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

  This file originates from QupZilla - WebKit based browser
  SPDX-FileCopyrightText: 2013-2014 David Rosca <nowrep@gmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ADBLOCKUTILS_H
#define ADBLOCKUTILS_H

#include <QString>

namespace AdBlock {
class AdblockUtil
{
public:
    static bool matchDomain(const QString &pattern, const QString &domain);
    template<typename T>
    static bool containsIndex(const T &container, int index)
    {
        return index >= 0 && container.count() > index;
    }

    static QMap<QString, QString> listSubscriptions();

    static QString localFilterPath();
    static QString filterCharsFromFilename(const QString &name);
    static QString ensureUniqueFilename(const QString &name, const QString &appendFormat = QStringLiteral("(%1)"));
};
}
#endif
