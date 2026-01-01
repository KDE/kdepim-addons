/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblocklistsutil.h"

QStringList AdblockListsUtil::adblockFilterNamesDefaultList()
{
    return {QStringLiteral("uBlock filters"),
            QStringLiteral("uBlock filters – Privacy"),
            QStringLiteral("uBlock filters – Resource abuse"),
            QStringLiteral("uBlock filters – Unbreak"),
            QStringLiteral("EasyPrivacy"),
            QStringLiteral("Easylist"),
            QStringLiteral("AdGuard Annoyances"),
            QStringLiteral("Adblock Warning Removal List")};
}

QList<QUrl> AdblockListsUtil::adblockFilterUrlsDefaultList()
{
    return {QUrl(QStringLiteral("https://raw.githubusercontent.com/uBlockOrigin/uAssets/master/filters/filters.txt")),
            QUrl(QStringLiteral("https://raw.githubusercontent.com/uBlockOrigin/uAssets/master/filters/privacy.txt")),
            QUrl(QStringLiteral("https://raw.githubusercontent.com/uBlockOrigin/uAssets/master/filters/resource-abuse.txt")),
            QUrl(QStringLiteral("https://raw.githubusercontent.com/uBlockOrigin/uAssets/master/filters/unbreak.txt")),
            QUrl(QStringLiteral("https://easylist.to/easylist/easyprivacy.txt")),
            QUrl(QStringLiteral("https://easylist.to/easylist/easylist.txt")),
            QUrl(QStringLiteral("https://filters.adtidy.org/extension/ublock/filters/14.txt")),
            QUrl(QStringLiteral("https://easylist-downloads.adblockplus.org/antiadblockfilters.txt"))};
}
