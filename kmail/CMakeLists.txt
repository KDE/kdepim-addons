# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_subdirectory(plugins)
add_subdirectory(editorplugins)
add_subdirectory(editorsendcheckplugins)
add_subdirectory(editorinitplugins)
add_subdirectory(editorconvertertextplugins)
add_subdirectory(grammarplugins)
add_subdirectory(checkbeforedeletemailplugins)
if(NOT WIN32)
    add_subdirectory(kcm)
endif()
