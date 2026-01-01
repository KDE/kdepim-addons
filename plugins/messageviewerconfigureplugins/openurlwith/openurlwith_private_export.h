/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "libopenurlwithconfigure_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef LIBOPENURLWITHCONFIGURE_TESTS_EXPORT
#define LIBOPENURLWITHCONFIGURE_TESTS_EXPORT LIBOPENURLWITHCONFIGURE_EXPORT
#endif
#else /* not compiling tests */
#define LIBOPENURLWITHCONFIGURE_TESTS_EXPORT
#endif
