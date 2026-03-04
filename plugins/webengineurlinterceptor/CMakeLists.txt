# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"webengineurlinterceptor\")
add_subdirectory(donottrack)
# Linking to Rust stuff causes undefined references to environ
# Disable adblock until a proper solution is found
if(Corrosion_FOUND AND NOT CMAKE_SYSTEM_NAME STREQUAL FreeBSD)
    add_subdirectory(adblock)
endif()
