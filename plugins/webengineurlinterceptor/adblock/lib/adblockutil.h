/*
  SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

  This file originates from QupZilla - WebKit based browser
  SPDX-FileCopyrightText: 2013-2014 David Rosca <nowrep@gmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QString>

namespace AdBlock
{
class AdblockUtil
{
public:
    static bool matchDomain(const QString &pattern, const QString &domain);
    template<typename T> static bool containsIndex(const T &container, int index)
    {
        return index >= 0 && container.count() > index;
    }

    static QMap<QString, QString> listSubscriptions();

    static Q_REQUIRED_RESULT QString localFilterPath();
    static Q_REQUIRED_RESULT QString filterCharsFromFilename(const QString &name);
    static Q_REQUIRED_RESULT QString ensureUniqueFilename(const QString &name, const QString &appendFormat = QStringLiteral("(%1)"));
};
}
