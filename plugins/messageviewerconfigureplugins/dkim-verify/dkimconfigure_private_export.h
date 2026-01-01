/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "libdkimverifyconfigure_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT
#define LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT LIBDKIMVERIFYCONFIGURE_EXPORT
#endif
#else /* not compiling tests */
#define LIBDKIMVERIFYCONFIGURE_TESTS_EXPORT
#endif
