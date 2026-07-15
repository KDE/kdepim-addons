# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"webengineurlinterceptor\")
add_subdirectory(donottrack)
# Adblock is enabled when Corrosion is available; linker-specific fixes are
# applied in adblock/CMakeLists.txt.
if(Corrosion_FOUND AND NOT CMAKE_SYSTEM_NAME STREQUAL FreeBSD)
    add_subdirectory(adblock)
endif()
