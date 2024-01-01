# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

add_definitions(-DTRANSLATION_DOMAIN=\"messageviewerplugins\")
add_subdirectory(createnoteplugin)
add_subdirectory(createtodoplugin)
add_subdirectory(createeventplugin)
add_subdirectory(common)
add_subdirectory(externalscriptplugin)
