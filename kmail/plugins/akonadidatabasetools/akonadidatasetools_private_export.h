/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "akonadidatasetools_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef AKONADIDATASETOOLS_TESTS_EXPORT
#define AKONADIDATASETOOLS_TESTS_EXPORT AKONADIDATASETOOLS_EXPORT
#endif
#else /* not compiling tests */
#define AKONADIDATASETOOLS_TESTS_EXPORT
#endif
