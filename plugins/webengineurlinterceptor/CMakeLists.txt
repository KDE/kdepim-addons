# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"webengineurlinterceptor\")
add_subdirectory(donottrack)
if (Corrosion_FOUND)
    add_subdirectory(adblock)
endif()
