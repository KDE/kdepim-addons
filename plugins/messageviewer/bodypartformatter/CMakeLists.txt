# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
add_subdirectory(ms-tnef)
add_subdirectory(vcard)
add_subdirectory(highlighter)
add_subdirectory(calendar)
add_subdirectory(gnupgwks)
add_subdirectory(pkpass)
if (TARGET KPim6::Itinerary)
   add_subdirectory(itinerary)
endif()

option(
    FORCE_DISCOUNT_LIB
    "Force using discount lib for markdown bodyformatter."
    TRUE
)
if(FORCE_DISCOUNT_LIB AND discount_FOUND)
    set(USE_DISCOUNT_LIB TRUE)
    message(STATUS "build bodyparformatter mardown with discount support")
    add_subdirectory(markdown)
else()
    set(USE_DISCOUNT_LIB FALSE)
    message(STATUS "build bodyparformatter mardown with QTextDocument support")
    add_subdirectory(markdown)
endif()
