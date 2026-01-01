/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "libadblockplugin_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef LIBADBLOCKPLUGIN_TESTS_EXPORT
#define LIBADBLOCKPLUGIN_TESTS_EXPORT LIBADBLOCKPLUGIN_EXPORT
#endif
#else /* not compiling tests */
#define LIBADBLOCKPLUGIN_TESTS_EXPORT
#endif
