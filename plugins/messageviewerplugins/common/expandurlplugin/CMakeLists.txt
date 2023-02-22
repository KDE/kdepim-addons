# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_expandurlplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/messageviewer/viewercommonplugin)
target_sources(messageviewer_expandurlplugin PRIVATE
    viewerpluginexpandurl.cpp
    viewerpluginexpandurlinterface.cpp
    viewerpluginexpandurl.h
    viewerpluginexpandurlinterface.h
    )

ecm_qt_declare_logging_category(messageviewer_expandurlplugin HEADER expandurlplugin_debug.h IDENTIFIER EXPANDURLPLUGIN_LOG CATEGORY_NAME org.kde.pim.expandurlplugin
    DESCRIPTION "kdepim-addons (Expand Url Plugin)"
    OLD_CATEGORY_NAMES log_expandurlplugin
    EXPORT KDEPIMADDONS
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_expandurlplugin PROPERTIES UNITY_BUILD ON)
endif()
target_link_libraries(messageviewer_expandurlplugin
    KF5::MessageViewer KF${KF_MAJOR_VERSION}::XmlGui KPim${KF_MAJOR_VERSION}::Libkdepim KF${KF_MAJOR_VERSION}::I18n
    )

