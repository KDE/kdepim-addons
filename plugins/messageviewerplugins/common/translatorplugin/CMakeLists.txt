# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_translatorplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/messageviewer/viewercommonplugin)
target_sources(messageviewer_translatorplugin PRIVATE
    viewerplugintranslator.cpp
    viewerplugintranslatorinterface.cpp
    viewerplugintranslator.h
    viewerplugintranslatorinterface.h
)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_translatorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_translatorplugin
  KF5::MessageViewer KF${KF_MAJOR_VERSION}::XmlGui KF5::PimTextEdit KF${KF_MAJOR_VERSION}::I18n
  KF${KF_MAJOR_VERSION}::TextTranslator
)
