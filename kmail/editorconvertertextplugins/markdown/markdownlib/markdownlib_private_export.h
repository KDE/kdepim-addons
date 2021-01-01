/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef LIBKMAILMARKDOWNPRIVATE_EXPORT_H
#define LIBKMAILMARKDOWNPRIVATE_EXPORT_H

#include "libkmailmarkdown_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
# ifndef LIBKMAILMARKDOWNPRIVATE_TESTS_EXPORT
#  define LIBKMAILMARKDOWNPRIVATE_TESTS_EXPORT LIBKMAILMARKDOWN_EXPORT
# endif
#else /* not compiling tests */
# define LIBKMAILMARKDOWNPRIVATE_TESTS_EXPORT
#endif

#endif
