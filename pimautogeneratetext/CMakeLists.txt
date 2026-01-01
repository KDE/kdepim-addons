# SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"libpimautogeneratetext\")

add_subdirectory(src)
if(BUILD_TESTING)
    add_subdirectory(tests)
    add_subdirectory(autotests)
endif()
