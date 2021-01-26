/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNUTIL_H
#define MARKDOWNUTIL_H

#include "libkmailmarkdown_export.h"
#include <QStringList>
namespace MarkdownUtil
{
LIBKMAILMARKDOWN_EXPORT QStringList imagePaths(const QString &str);
}

#endif // MARKDOWNUTIL_H
