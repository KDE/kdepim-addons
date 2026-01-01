# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_subdirectory(translatorplugin)
add_subdirectory(expandurlplugin)

if(TARGET KF6::TextAutoGenerateText)
    add_subdirectory(messagevieweraiplugin)
endif()

