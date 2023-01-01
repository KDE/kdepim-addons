/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "libscamconfiguresettings_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef LIBSCAMCONFIGURESETTINGS_TESTS_EXPORT
#define LIBSCAMCONFIGURESETTINGS_TESTS_EXPORT LIBSCAMCONFIGURESETTINGS_EXPORT
#endif
#else /* not compiling tests */
#define LIBSCAMCONFIGURESETTINGS_TESTS_EXPORT
#endif
