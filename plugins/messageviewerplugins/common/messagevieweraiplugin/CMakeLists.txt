# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(messageviewer_aiplugin INSTALL_NAMESPACE pim6/messageviewer/viewercommonplugin)
target_sources(
    messageviewer_aiplugin
    PRIVATE
    viewerpluginai.cpp
    viewerpluginai.h
    viewerpluginaiinterface.cpp
    viewerpluginaiinterface.h
    viewerpluginaiwidget.h
    viewerpluginaiwidget.cpp
)

ecm_qt_declare_logging_category(messageviewer_aiplugin HEADER expandurlplugin_debug.h IDENTIFIER EXPANDURLPLUGIN_LOG CATEGORY_NAME org.kde.pim.expandurlplugin
    DESCRIPTION "kdepim-addons (AI Plugin)"
    EXPORT KDEPIMADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        messageviewer_aiplugin
        PROPERTIES UNITY_BUILD ON
    )
endif()
target_link_libraries(
    messageviewer_aiplugin
    KPim6::MessageViewer
    KF6::XmlGui
    KPim6::Libkdepim
    KF6::I18n
)
