/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "adblockplugin_private_export.h"
#include <QStringList>
#include <QUrl>
namespace AdblockListsUtil
{
[[nodiscard]] LIBADBLOCKPLUGIN_TESTS_EXPORT QStringList adblockFilterNamesDefaultList();
[[nodiscard]] LIBADBLOCKPLUGIN_TESTS_EXPORT QList<QUrl> adblockFilterUrlsDefaultList();
};
