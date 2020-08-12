/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNUTIL_H
#define MARKDOWNUTIL_H

#include <QStringList>
#include "libkmailmarkdown_export.h"
namespace MarkdownUtil {
LIBKMAILMARKDOWN_EXPORT QStringList imagePaths(const QString &str);
}

#endif // MARKDOWNUTIL_H
