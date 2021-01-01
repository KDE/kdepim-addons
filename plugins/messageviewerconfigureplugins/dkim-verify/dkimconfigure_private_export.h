/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMCONFIGUREPRIVATE_EXPORT_H
#define DKIMCONFIGUREPRIVATE_EXPORT_H

#include "libdkimverifyconfigure_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
    #ifndef MESSAGEVIEWER_TESTS_EXPORT
        #define LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT LIBDKIMVERIFYCONFIGURE_EXPORT
    # endif
#else /* not compiling tests */
    #define LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT
#endif

#endif
