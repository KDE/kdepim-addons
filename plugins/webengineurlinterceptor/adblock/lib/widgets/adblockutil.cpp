/*
   Copyright (C) 2013-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "adblockutil.h"

#include <QStandardPaths>

QMap<QString, QString> AdBlock::AdBlockUtil::listSubscriptions()
{
    QMap<QString, QString> lst;
    lst.insert(QStringLiteral("EasyList"), QStringLiteral("https://easylist-downloads.adblockplus.org/easylist.txt"));
    lst.insert(QStringLiteral("EasyList without element hiding"), QStringLiteral("https://easylist-downloads.adblockplus.org/easylist_noelemhide.txt"));
    lst.insert(QStringLiteral("Corset"), QStringLiteral("http://brianyi.com/corset.txt"));
    lst.insert(QStringLiteral("EasyList Germany"), QStringLiteral("https://easylist-downloads.adblockplus.org/easylistgermany.txt"));
    lst.insert(QStringLiteral("Liste FR+EasyList"), QStringLiteral("https://easylist-downloads.adblockplus.org/liste_fr+easylist.txt"));
    lst.insert(QStringLiteral("ROList+EasyList"), QStringLiteral("https://easylist-downloads.adblockplus.org/rolist+easylist.txt"));
    lst.insert(QStringLiteral("AdblockList.org"), QStringLiteral("http://adblocklist.org/adblock-pxf-polish.txt"));
    lst.insert(QStringLiteral("Bulgarian list"), QStringLiteral("http://stanev.org/abp/adblock_bg.txt"));
    lst.insert(QStringLiteral("EasyPrivacy+EasyList"), QStringLiteral("https://easylist-downloads.adblockplus.org/easyprivacy+easylist.txt"));
    lst.insert(QStringLiteral("EasyPrivacy"), QStringLiteral("https://easylist-downloads.adblockplus.org/easyprivacy.txt"));
    lst.insert(QStringLiteral("void.gr"), QStringLiteral("http://www.void.gr/kargig/void-gr-filters.txt"));
    lst.insert(QStringLiteral("BSI Lista Polska"), QStringLiteral("http://www.bsi.info.pl/filtrABP.txt"));
    lst.insert(QStringLiteral("Czech List"), QStringLiteral("http://dajbych.net/adblock.txt"));
    lst.insert(QStringLiteral("Cédrics Liste"), QStringLiteral("http://chewey.de/mozilla/data/adblock.txt"));
    lst.insert(QStringLiteral("Fanboy's List"), QStringLiteral("http://www.fanboy.co.nz/adblock/fanboy-adblocklist-current-expanded.txt"));
    lst.insert(QStringLiteral("hufilter"), QStringLiteral("http://pete.teamlupus.hu/hufilter.txt"));
    lst.insert(QStringLiteral("Japanese Site-Specific Filter"), QStringLiteral("http://adblock-plus-japanese-filter.googlecode.com/svn/trunk/abp_jp_site_specific.txt"));
    lst.insert(QStringLiteral("NLBlock"), QStringLiteral("http://www.verzijlbergh.com/adblock/nlblock.txt"));
    lst.insert(QStringLiteral("PLgeneral"), QStringLiteral("http://www.niecko.pl/adblock/adblock.txt"));
    lst.insert(QStringLiteral("Schacks Adblock Plus liste"), QStringLiteral("http://adblock.schack.dk/block.txt"));
    lst.insert(QStringLiteral("Xfiles"), QStringLiteral("http://mozilla.gfsolone.com/filtri.txt"));
    lst.insert(QStringLiteral("adblock.free.fr"), QStringLiteral("http://adblock.free.fr/adblock.txt"));
    lst.insert(QStringLiteral("adblock.free.fr basic (bloque les pubs uniquement)"), QStringLiteral("http://adblock.free.fr/adblock_basic.txt"));
    lst.insert(QStringLiteral("Ajnasz's list"), QStringLiteral("http://ajnasz.hu/adblock/recent"));
    lst.insert(QStringLiteral("Schuzak's Universal Filter"), QStringLiteral("http://www.schuzak.jp/other/abp.txt"));
    lst.insert(QStringLiteral("Rickroll Blacklist"), QStringLiteral("http://rickrolldb.com/ricklist.txt"));
    return lst;
}

QString AdBlock::AdBlockUtil::localFilterPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QStringLiteral("/adblock/adblockrules_local");
}
