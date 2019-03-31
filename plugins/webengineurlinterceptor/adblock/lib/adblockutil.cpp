/*
  Copyright (c) 2016-2019 Montel Laurent <montel@kde.org>
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2010-2014  David Rosca <nowrep@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
* ============================================================ */
#include "adblockutil.h"

#include <QDir>
#include <QFileInfo>
#include <QMap>
#include <QStandardPaths>

using namespace AdBlock;
// Matches domain (assumes both pattern and domain not starting with dot)
//  pattern = domain to be matched
//  domain = site domain
bool AdblockUtil::matchDomain(const QString &pattern, const QString &domain)
{
    if (pattern == domain) {
        return true;
    }

    if (!domain.endsWith(pattern)) {
        return false;
    }

    int index = domain.indexOf(pattern);

    return index > 0 && domain[index - 1] == QLatin1Char('.');
}

QMap<QString, QString> AdBlock::AdblockUtil::listSubscriptions()
{
    QMap<QString, QString> lst;
    lst.insert(QStringLiteral("EasyList"), QStringLiteral("https://easylist-downloads.adblockplus.org/easylist.txt"));
    lst.insert(QStringLiteral("EasyList without element hiding"), QStringLiteral("https://easylist-downloads.adblockplus.org/easylist_noelemhide.txt"));
    lst.insert(QStringLiteral("EasyList Germany"), QStringLiteral("https://easylist-downloads.adblockplus.org/easylistgermany.txt"));
    lst.insert(QStringLiteral("Liste FR+EasyList"), QStringLiteral("https://easylist-downloads.adblockplus.org/liste_fr+easylist.txt"));
    lst.insert(QStringLiteral("ROList+EasyList"), QStringLiteral("https://easylist-downloads.adblockplus.org/rolist+easylist.txt"));
    lst.insert(QStringLiteral("AdblockList.org"), QStringLiteral("http://adblocklist.org/adblock-pxf-polish.txt"));
    lst.insert(QStringLiteral("Bulgarian list"), QStringLiteral("https://stanev.org/abp/adblock_bg.txt"));
    lst.insert(QStringLiteral("EasyPrivacy+EasyList"), QStringLiteral("https://easylist-downloads.adblockplus.org/easyprivacy+easylist.txt"));
    lst.insert(QStringLiteral("EasyPrivacy"), QStringLiteral("https://easylist-downloads.adblockplus.org/easyprivacy.txt"));
    lst.insert(QStringLiteral("void.gr"), QStringLiteral("https://www.void.gr/kargig/void-gr-filters.txt"));
    lst.insert(QStringLiteral("Czech List"), QStringLiteral("https://dajbych.net/adblock.txt"));
    lst.insert(QStringLiteral("Cédrics Liste"), QStringLiteral("https://chewey.de/mozilla/data/adblock.txt"));
    lst.insert(QStringLiteral("Fanboy's List"), QStringLiteral("https://www.fanboy.co.nz/adblock/fanboy-adblocklist-current-expanded.txt"));
    lst.insert(QStringLiteral("PLgeneral"), QStringLiteral("https://www.niecko.pl/adblock/adblock.txt"));
    lst.insert(QStringLiteral("Schacks Adblock Plus liste"), QStringLiteral("https://adblock.schack.dk/block.txt"));
    lst.insert(QStringLiteral("adblock.free.fr"), QStringLiteral("http://adblock.free.fr/adblock.txt"));
    lst.insert(QStringLiteral("adblock.free.fr basic (bloque les pubs uniquement)"), QStringLiteral("http://adblock.free.fr/adblock_basic.txt"));
    lst.insert(QStringLiteral("Ajnasz's list"), QStringLiteral("https://ajnasz.hu/adblock/recent"));
    lst.insert(QStringLiteral("Rickroll Blacklist"), QStringLiteral("https://rickrolldb.com/ricklist.txt"));
    return lst;
}

QString AdBlock::AdblockUtil::localFilterPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QStringLiteral("/adblock/customlist.txt");
}

QString AdBlock::AdblockUtil::filterCharsFromFilename(const QString &name)
{
    QString value = name;

    value.replace(QLatin1Char('/'), QLatin1Char('-'));
    value.remove(QLatin1Char('\\'));
    value.remove(QLatin1Char(':'));
    value.remove(QLatin1Char('*'));
    value.remove(QLatin1Char('?'));
    value.remove(QLatin1Char('"'));
    value.remove(QLatin1Char('<'));
    value.remove(QLatin1Char('>'));
    value.remove(QLatin1Char('|'));

    return value;
}

QString AdBlock::AdblockUtil::ensureUniqueFilename(const QString &name, const QString &appendFormat)
{
    Q_ASSERT(appendFormat.contains(QStringLiteral("%1")));

    QFileInfo info(name);

    if (!info.exists()) {
        return name;
    }

    const QDir dir = info.absoluteDir();
    const QString fileName = info.fileName();

    int i = 1;

    while (info.exists()) {
        QString file = fileName;
        int index = file.lastIndexOf(QLatin1Char('.'));
        const QString appendString = appendFormat.arg(i);
        if (index == -1) {
            file.append(appendString);
        } else {
            file = file.left(index) + appendString + file.mid(index);
        }
        info.setFile(dir, file);
        i++;
    }

    return info.absoluteFilePath();
}
