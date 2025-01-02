/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "kmailconfirmbeforedeleting_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef KMAILCONFIRMBEFOREDELETING_TESTS_EXPORT
#define KMAILCONFIRMBEFOREDELETING_TESTS_EXPORT KMAILCONFIRMBEFOREDELETING_EXPORT
#endif
#else /* not compiling tests */
#define KMAILCONFIRMBEFOREDELETING_TESTS_EXPORT
#endif
