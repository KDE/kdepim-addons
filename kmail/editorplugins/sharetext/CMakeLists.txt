# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_sharetexteditorplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kmail/plugineditor)
target_sources(kmail_sharetexteditorplugin PRIVATE
    sharetextplugineditor.cpp
    sharetextplugineditorinterface.cpp
    sharetextpurposemenuwidget.cpp
    sharetextplugineditor.h
    sharetextplugineditorinterface.h
    sharetextpurposemenuwidget.h
    )

ecm_qt_declare_logging_category(kmail_sharetexteditorplugin HEADER sharetexteditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_SHARETEXT_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_sharetexteditorplugin
    DESCRIPTION "kdepim-addons (share text editor plugin)"
    EXPORT KDEPIMADDONS
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_sharetexteditorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_sharetexteditorplugin
    KPim${KF_MAJOR_VERSION}::MessageComposer KF${KF_MAJOR_VERSION}::XmlGui KF${KF_MAJOR_VERSION}::I18n
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

