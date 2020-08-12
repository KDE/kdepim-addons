/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef LIBLANGUAGETOOLPRIVATE_EXPORT_H
#define LIBLANGUAGETOOLPRIVATE_EXPORT_H

#include "libkmaillanguagetool_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
# ifndef LIBLANGUAGETOOLPRIVATE_TESTS_EXPORT
#  define LIBLANGUAGETOOLPRIVATE_TESTS_EXPORT LIBKMAILLANGUAGETOOL_EXPORT
# endif
#else /* not compiling tests */
# define LIBLANGUAGETOOLPRIVATE_TESTS_EXPORT
#endif

#endif
