# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_subdirectory(translatorplugin)
add_subdirectory(expandurlplugin)

if(TARGET KF6::TextAutoGenerateText)
    if(${KF6TextAutoGenerateText_VERSION} VERSION_GREATER_EQUAL 1.8.59)
        add_subdirectory(messagevieweraiplugin)
    endif()
endif()

