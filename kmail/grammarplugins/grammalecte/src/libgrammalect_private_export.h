/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef LIBGRAMMALECTPRIVATE_EXPORT_H
#define LIBGRAMMALECTPRIVATE_EXPORT_H

#include "libkmailgrammalecte_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
# ifndef LIBGRAMMALECTPRIVATE_TESTS_EXPORT
#  define LIBGRAMMALECTPRIVATE_TESTS_EXPORT LIBKMAILGRAMMALECTE_EXPORT
# endif
#else /* not compiling tests */
# define LIBGRAMMALECTPRIVATE_TESTS_EXPORT
#endif

#endif
