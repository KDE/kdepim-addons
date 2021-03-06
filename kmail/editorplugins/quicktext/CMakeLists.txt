# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_library(kmailquicktextpluginprivate)
target_sources(kmailquicktextpluginprivate PRIVATE
    quicktextmenu.cpp
    quicktextconfigurewidget.cpp
    quicktextconfiguredialog.cpp
    quicktextmanager.cpp
    quicktexttreewidget.cpp
    quicktextwidget.cpp
    )


generate_export_header(kmailquicktextpluginprivate BASE_NAME quicktext)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmailquicktextpluginprivate PROPERTIES UNITY_BUILD ON)
endif()


target_link_libraries(kmailquicktextpluginprivate
    PRIVATE
    KF5::I18n KF5::CoreAddons Qt::Gui Qt::Widgets KF5::MessageComposer KF5::MailCommon KF5::XmlGui
    )

set_target_properties(kmailquicktextpluginprivate
    PROPERTIES VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )

install(TARGETS kmailquicktextpluginprivate ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
kcoreaddons_add_plugin(kmail_quicktextplugin INSTALL_NAMESPACE kmail/plugineditor)
target_sources(kmail_quicktextplugin PRIVATE
    quicktextplugineditor.cpp
    quicktextplugineditorinterface.cpp
    )

ecm_qt_declare_logging_category(kmail_quicktextplugin HEADER quicktextplugin_debug.h IDENTIFIER KMAIL_EDITOR_QUICKTEXT_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_quicktextplugin
    DESCRIPTION "kdepim-addons (kmail quicktext editor plugin)"
    EXPORT KDEPIMADDONS
    )



if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_quicktextplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_quicktextplugin
    KF5::MessageComposer KF5::XmlGui KF5::I18n kmailquicktextpluginprivate KF5::MailCommon
    )
