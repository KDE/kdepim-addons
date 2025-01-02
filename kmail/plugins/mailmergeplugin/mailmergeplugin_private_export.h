/*  This file is part of the KDE project
    SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "mailmerge_export.h"

/* Classes which are exported only for unit tests */
#ifdef BUILD_TESTING
#ifndef MAILMERGEPRIVATE_TESTS_EXPORT
#define MAILMERGEPRIVATE_TESTS_EXPORT MAILMERGE_EXPORT
#endif
#else /* not compiling tests */
#define MAILMERGEPRIVATE_TESTS_EXPORT
#endif
