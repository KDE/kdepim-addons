/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "pimautogeneratetext_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef PIMAUTOGENERATETEXT_TESTS_EXPORT
#define PIMAUTOGENERATETEXT_TESTS_EXPORT PIMAUTOGENERATETEXT_EXPORT
#endif
#else /* not compiling tests */
#define PIMAUTOGENERATETEXT_TESTS_EXPORT
#endif
