# SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_BINARY_DIR}/
)

configure_file(config-markdownplugin.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-markdownplugin.h)

add_subdirectory(markdownlib)
add_subdirectory(plugin)
if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()
