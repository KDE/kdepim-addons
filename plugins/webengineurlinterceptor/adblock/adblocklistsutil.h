/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QStringList>
#include <QUrl>
namespace AdblockListsUtil
{
QStringList adblockFilterNamesDefaultList();
QList<QUrl> adblockFilterUrlsDefaultList();
};
