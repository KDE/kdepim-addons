# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_translatorplugin INSTALL_NAMESPACE pim6/messageviewer/viewercommonplugin)
target_sources(
    messageviewer_translatorplugin
    PRIVATE
        viewerplugintranslator.cpp
        viewerplugintranslatorinterface.cpp
        viewerplugintranslator.h
        viewerplugintranslatorinterface.h
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        messageviewer_translatorplugin
        PROPERTIES UNITY_BUILD ON
    )
endif()

target_link_libraries(
    messageviewer_translatorplugin
    KPim6::MessageViewer
    KF6::XmlGui
    KPim6::PimTextEdit
    KF6::I18n
    KF6::TextTranslator
)
