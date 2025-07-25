# SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_library(scamconfiguresettings)

target_sources(
    scamconfiguresettings
    PRIVATE
        scamconfiguresettingsdialog.cpp
        scamconfiguresettingswidget.cpp
        scamconfigureutils.cpp
        scamconfiguresettingsdialog.h
        scamconfiguresettingswidget.h
        scamconfigureutils.h
        scamconfiguresettingstreeview.h
        scamconfiguresettingstreeview.cpp
        scamlistsmodel.h
        scamlistsmodel.cpp
)

ecm_qt_declare_logging_category(scamconfiguresettings HEADER libscamconfiguresettings_debug.h IDENTIFIER LIBSCAMCONFIGURESETTINGS_PLUGIN_LOG CATEGORY_NAME org.kde.pim.libfolderconfiguresettingsplugin
    DESCRIPTION "kdepim-addons (scamettings-configure)"
    EXPORT KDEPIMADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(scamconfiguresettings PROPERTIES UNITY_BUILD ON)
endif()

generate_export_header(scamconfiguresettings BASE_NAME libscamconfiguresettings)
target_link_libraries(scamconfiguresettings KPim6::MessageViewer KF6::I18n)

set_target_properties(
    scamconfiguresettings
    PROPERTIES
        OUTPUT_NAME scamconfiguresettings
        VERSION ${KDEPIMADDONS_LIB_VERSION}
        SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
)

install(
    TARGETS scamconfiguresettings ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY NAMELINK_SKIP
)

######
kcoreaddons_add_plugin(messageviewer_scamconfiguresettingsplugin INSTALL_NAMESPACE pim6/messageviewer/configuresettings)

target_sources(
    messageviewer_scamconfiguresettingsplugin
    PRIVATE scamconfiguresettingsplugin.cpp scamconfiguresettingsplugin.h
)

target_link_libraries(
    messageviewer_scamconfiguresettingsplugin
    KPim6::MessageViewer
    scamconfiguresettings
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
