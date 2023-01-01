/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownutil.h"
#include <QRegularExpression>

QStringList MarkdownUtil::imagePaths(const QString &str)
{
    static QRegularExpression imageRegular(QStringLiteral("!\\[.*\\]\\((.*)([\\s]*=.*x.*)*\\s*([\\s]*\".*\")*\\s*\\)"));

    imageRegular.setPatternOptions(QRegularExpression::InvertedGreedinessOption);
    QRegularExpressionMatchIterator i = imageRegular.globalMatch(str);
    QStringList results;
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if (match.hasMatch()) {
            results.append(match.captured(1));
        }
    }
    return results;
}
