# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_library(expireaccounttrashfolderconfig)
target_sources(expireaccounttrashfolderconfig PRIVATE
    expireaccounttrashfolderconfigdialog.cpp
    expireaccounttrashfolderconfigwidget.cpp

    expireaccounttrashfolderconfigdialog.h
    expireaccounttrashfolderconfigwidget.h
    )

ecm_qt_declare_logging_category(expireaccounttrashfolderconfig HEADER libexpireaccounttrashfolderconfig_debug.h IDENTIFIER LIBEXPIREACCOUNTTRASHFOLDERCONFIG_PLUGIN_LOG CATEGORY_NAME org.kde.pim.libexpireaccounttrashfolderconfig
    DESCRIPTION "kdepim-addons (expire account trash folder config)"
    EXPORT KDEPIMADDONS
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(expireaccounttrashfolderconfig PROPERTIES UNITY_BUILD ON)
endif()

generate_export_header(expireaccounttrashfolderconfig BASE_NAME libexpireaccounttrashfolderconfig)
target_link_libraries(expireaccounttrashfolderconfig
    KF5::MessageViewer
    KF${KF_MAJOR_VERSION}::I18n
    KF5::MailCommon
    )

set_target_properties(expireaccounttrashfolderconfig
    PROPERTIES OUTPUT_NAME expireaccounttrashfolderconfig VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )

install(TARGETS expireaccounttrashfolderconfig ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)



kcoreaddons_add_plugin(messageviewer_expireaccounttrashfolderconfigplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/messageviewer/configuresettings)
target_sources(messageviewer_expireaccounttrashfolderconfigplugin PRIVATE
   expireaccounttrashfolderconfigplugin.cpp
   expireaccounttrashfolderconfigplugin.h
)

target_link_libraries(messageviewer_expireaccounttrashfolderconfigplugin
  KF5::MessageViewer
  KF${KF_MAJOR_VERSION}::I18n
  KF5::MailCommon
  expireaccounttrashfolderconfig
)


if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
