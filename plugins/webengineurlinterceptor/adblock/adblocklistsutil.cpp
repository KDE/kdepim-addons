/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblocklistsutil.h"
using namespace Qt::Literals::StringLiterals;

QStringList AdblockListsUtil::adblockFilterNamesDefaultList()
{
    return {u"uBlock filters"_s,
            u"uBlock filters – Privacy"_s,
            u"uBlock filters – Resource abuse"_s,
            u"uBlock filters – Unbreak"_s,
            u"EasyPrivacy"_s,
            u"Easylist"_s,
            u"AdGuard Annoyances"_s,
            u"Adblock Warning Removal List"_s};
}

QList<QUrl> AdblockListsUtil::adblockFilterUrlsDefaultList()
{
    return {QUrl(u"https://raw.githubusercontent.com/uBlockOrigin/uAssets/master/filters/filters.txt"_s),
            QUrl(u"https://raw.githubusercontent.com/uBlockOrigin/uAssets/master/filters/privacy.txt"_s),
            QUrl(u"https://raw.githubusercontent.com/uBlockOrigin/uAssets/master/filters/resource-abuse.txt"_s),
            QUrl(u"https://raw.githubusercontent.com/uBlockOrigin/uAssets/master/filters/unbreak.txt"_s),
            QUrl(u"https://easylist.to/easylist/easyprivacy.txt"_s),
            QUrl(u"https://easylist.to/easylist/easylist.txt"_s),
            QUrl(u"https://filters.adtidy.org/extension/ublock/filters/14.txt"_s),
            QUrl(u"https://easylist-downloads.adblockplus.org/antiadblockfilters.txt"_s)};
}
