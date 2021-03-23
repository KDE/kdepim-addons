/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "libkmailmarkdown_export.h"
#include <QStringList>
namespace MarkdownUtil
{
LIBKMAILMARKDOWN_EXPORT QStringList imagePaths(const QString &str);
}

