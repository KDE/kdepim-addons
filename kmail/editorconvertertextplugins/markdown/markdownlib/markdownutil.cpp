/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownutil.h"
#include <QRegularExpression>
using namespace Qt::Literals::StringLiterals;

QStringList MarkdownUtil::imagePaths(const QString &str)
{
    static QRegularExpression imageRegular(u"!\\[.*\\]\\((.*)([\\s]*=.*x.*)*\\s*([\\s]*\".*\")*\\s*\\)"_s);

    imageRegular.setPatternOptions(QRegularExpression::InvertedGreedinessOption);
    QRegularExpressionMatchIterator i = imageRegular.globalMatchView(str);
    QStringList results;
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if (match.hasMatch()) {
            results.append(match.captured(1));
        }
    }
    return results;
}
