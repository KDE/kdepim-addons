/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "libfolderconfiguresettings_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef LIBFOLDERCONFIGURESETTINGS_TESTS_EXPORT
#define LIBFOLDERCONFIGURESETTINGS_TESTS_EXPORT LIBFOLDERCONFIGURESETTINGS_EXPORT
#endif
#else /* not compiling tests */
#define LIBFOLDERCONFIGURESETTINGS_TESTS_EXPORT
#endif
