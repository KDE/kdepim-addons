# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_library(shorturlpluginprivate)
target_sources(shorturlpluginprivate PRIVATE
    shorturlengineplugin/shorturlengineinterface.cpp
    shorturlengineplugin/shorturlengineplugin.cpp
    shorturlengineplugin/shorturlenginepluginmanager.cpp
    )


generate_export_header(shorturlpluginprivate BASE_NAME shorturl)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(shorturlpluginprivate PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(shorturlpluginprivate
    PRIVATE
    Qt::Network KF5::I18n KF5::CoreAddons Qt::Gui
    )

set_target_properties(shorturlpluginprivate
    PROPERTIES VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )

install(TARGETS shorturlpluginprivate ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)



add_subdirectory(shorturlengineplugin)
kcoreaddons_add_plugin(kmail_insertshorturleditorplugin INSTALL_NAMESPACE kmail/plugineditor)

target_sources(kmail_insertshorturleditorplugin PRIVATE
    insertshorturlplugineditor.cpp
    insertshorturlplugineditorinterface.cpp
    insertshorturlconfiguredialog.cpp
    insertshorturlconfigurewidget.cpp
    ${pimcommon_shorturlplugin_shorturllib_SRCS}
    )
ecm_qt_declare_logging_category(kmail_insertshorturleditorplugin HEADER kmail_insertshorturl_debug.h IDENTIFIER KMAIL_INSERTSHORTURL_LOG CATEGORY_NAME org.kde.pim.kmail_insertshorturl
    DESCRIPTION "kdepim-addons (kmail insert short url plugin)"
    EXPORT KDEPIMADDONS
    )


target_link_libraries(kmail_insertshorturleditorplugin
    KF5::MessageComposer KF5::XmlGui KF5::I18n shorturlpluginprivate KF5::CoreAddons
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()


