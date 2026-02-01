# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"messageviewerheaderplugins\")
add_subdirectory(briefheaderstyleplugin)
add_subdirectory(fancyheaderstyleplugin)
add_subdirectory(grantleeheaderstyleplugin)
add_subdirectory(longheaderstyleplugin)
add_subdirectory(standardsheaderstyleplugin)
if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()
