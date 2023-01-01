# SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_markdownplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kmail/plugineditorconverttext)
target_sources(kmail_markdownplugin PRIVATE
    markdowninterface.cpp
    markdownplugin.cpp
    markdowninterface.h
    markdownplugin.h
    )

ecm_qt_declare_logging_category(kmail_markdownplugin HEADER markdownplugin_debug.h IDENTIFIER KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_markdownplugin)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_markdownplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_markdownplugin PRIVATE
    KF5::I18n KF5::XmlGui
    kmailmarkdown
    )

