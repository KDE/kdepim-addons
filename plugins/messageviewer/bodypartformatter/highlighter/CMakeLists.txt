# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_text_xdiff_plugin\")
add_library(messageviewer_bodypartformatter_text_highlighter MODULE )
target_sources(messageviewer_bodypartformatter_text_highlighter PRIVATE texthighlighterplugin.cpp highlighter.cpp highlighter.h)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_bodypartformatter_text_highlighter PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_bodypartformatter_text_highlighter
    Qt::Core
    KPim6::MessageViewer
    KF6::SyntaxHighlighting
    KF6::TextTemplate
)

install(TARGETS messageviewer_bodypartformatter_text_highlighter DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim6/messageviewer/bodypartformatter)
