# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_dkimconfigplugin INSTALL_NAMESPACE pim6/messageviewer/configuresettings)
target_sources(
    messageviewer_dkimconfigplugin
    PRIVATE dkimconfiguresettingsplugin.cpp dkimconfiguresettingsplugin.h
)

target_link_libraries(
    messageviewer_dkimconfigplugin
    KPim6::MessageViewer
    KF6::I18n
    dkimverifyconfigure
)

add_library(dkimverifyconfigure)
target_sources(
    dkimverifyconfigure
    PRIVATE
        dkimconfiguredialog.cpp
        dkimconfiguretab.cpp
        dkimconfigurewidget.cpp
        dkimgeneralwidget.cpp
        dkimkeyrecordwidget.cpp
        dkimadvancedwidget.cpp
        dkimpolicywidget.cpp
        dkimauthenticationverifiedserverwidget.cpp
        dkimauthenticationverifiedserverdialog.cpp
        dkimconfiguredialog.h
        dkimconfiguretab.h
        dkimconfigurewidget.h
        dkimgeneralwidget.h
        dkimkeyrecordwidget.h
        dkimadvancedwidget.h
        dkimpolicywidget.h
        dkimauthenticationverifiedserverwidget.h
        dkimauthenticationverifiedserverdialog.h
)

ecm_qt_declare_logging_category(dkimverifyconfigure HEADER libdkimverifyconfigure_debug.h IDENTIFIER LIBDKIMVERIFYCONFIGURE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.libdkimconfigureplugin
    DESCRIPTION "kdepim-addons (dkim-verify-configure)"
    EXPORT KDEPIMADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(dkimverifyconfigure PROPERTIES UNITY_BUILD ON)
endif()

generate_export_header(dkimverifyconfigure BASE_NAME libdkimverifyconfigure)
target_link_libraries(
    dkimverifyconfigure
    KF6::I18n
    KF6::ConfigCore
    KF6::WidgetsAddons
    KPim6::MessageViewer
    KF6::ConfigWidgets
    KF6::ItemViews
)

set_target_properties(
    dkimverifyconfigure
    PROPERTIES
        OUTPUT_NAME dkimverifyconfigure
        VERSION ${KDEPIMADDONS_LIB_VERSION}
        SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
)

install(
    TARGETS dkimverifyconfigure ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY NAMELINK_SKIP
)
if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
