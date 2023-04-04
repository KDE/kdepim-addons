# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set(mardown_engine_SRCS)
set(discount_LIB)
add_library(messageviewer_bodypartformatter_text_markdown MODULE)
if(USE_DISCOUNT_LIB)
    add_definitions(-DUSE_DISCOUNT_LIB)
    target_sources(messageviewer_bodypartformatter_text_markdown PRIVATE markdowndiscount.cpp markdowndiscount.h)
    target_link_libraries(messageviewer_bodypartformatter_text_markdown discount::Lib)
else()
    target_sources(messageviewer_bodypartformatter_text_markdown PRIVATE markdownqtextdocument.cpp markdownqtextdocument.h)
endif()

add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_text_markdown_plugin\")
target_sources(messageviewer_bodypartformatter_text_markdown PRIVATE textmarkdownplugin.cpp markdownabstract.cpp markdownabstract.h)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_bodypartformatter_text_markdown PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_bodypartformatter_text_markdown
    Qt::Core
    KPim6::MessageViewer
    ${TEMPLATES_LIB}
)
install(TARGETS messageviewer_bodypartformatter_text_markdown DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim${QT_MAJOR_VERSION}/messageviewer/bodypartformatter)
