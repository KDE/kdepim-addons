# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_custom_target(adblock
    SOURCES
    rs/adblock/Cargo.toml
    rs/adblock/build.rs
    rs/adblock/src/lib.rs
    rs/adblock/src/adblock.rs
    rs/adblock/src/domainresolver.rs
    rs/adblock/src/logging.rs
)

corrosion_import_crate(MANIFEST_PATH ${CMAKE_CURRENT_SOURCE_DIR}/rs/adblock/Cargo.toml)

add_library(adblockplugin)

target_include_directories(adblockplugin PRIVATE
    ${CMAKE_BINARY_DIR}/cargo/build/${Rust_CARGO_TARGET}/cxxbridge/webengineviewer-adblock/src/)

target_sources(adblockplugin PRIVATE
    adblockfilterlistsmodel.h
    adblockfilterlistsmodel.cpp
    adblockfilter.h
    adblockfilter.cpp
    adblockpluginurlinterceptorconfiguredialog.cpp
    adblockpluginurlinterceptorconfiguredialog.h
    adblockpluginurlinterceptorconfigurewidget.cpp
    adblockpluginurlinterceptorconfigurewidget.h
    adblockfiltertreeview.h
    adblockfiltertreeview.cpp
    adblockfilterdialog.h
    adblockfilterdialog.cpp
    adblockfilterwidget.h
    adblockfilterwidget.cpp
    adblockmanager.h
    adblockmanager.cpp

    adblocklistsmanager.h
    adblocklistsmanager.cpp

    adblockpluginurlinterceptoraddadblocklistdialog.h
    adblockpluginurlinterceptoraddadblocklistdialog.cpp

    adblockpluginurlinterceptoraddadblocklistwidget.h
    adblockpluginurlinterceptoraddadblocklistwidget.cpp

    adblockplugin_private_export.h
    adblocklistsutil.h
    adblocklistsutil.cpp

    adblockviewfilterdialog.h
    adblockviewfilterdialog.cpp

    adblockviewfilterwidget.h
    adblockviewfilterwidget.cpp
)

kconfig_add_kcfg_files(adblockplugin
    settings/globalsettings_webengineurlinterceptoradblock.kcfgc
)

ecm_qt_declare_logging_category(adblockplugin HEADER libadblockplugin_debug.h IDENTIFIER LIBADBLOCKPLUGIN_PLUGIN_LOG
    CATEGORY_NAME org.kde.pim.libadblockplugin
    DESCRIPTION "kdepim-addons (adblockplugin lib)"
    EXPORT KDEPIMADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(adblockplugin PROPERTIES UNITY_BUILD ON)
endif()

generate_export_header(adblockplugin BASE_NAME libadblockplugin)
target_link_libraries(adblockplugin
    KF6::I18n
    Qt::WebEngineWidgets
    KPim6::WebEngineViewer
    KF6::TextCustomEditor
)
if(Corrosion_VERSION VERSION_LESS 0.5.0)
    target_link_libraries(adblockplugin webengineviewer-adblock)
else()
    target_link_libraries(adblockplugin webengineviewer_adblock)
endif()

set_target_properties(adblockplugin
    PROPERTIES OUTPUT_NAME adblockplugin VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
)

install(TARGETS adblockplugin ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

kcoreaddons_add_plugin(webengineviewer_adblockplugin INSTALL_NAMESPACE pim6/webengineviewer/urlinterceptor)
target_sources(webengineviewer_adblockplugin PRIVATE
    adblockinterceptorinterface.cpp
    adblockinterceptorinterface.h
    adblockpluginurlinterceptor.cpp
    adblockpluginurlinterceptor.h
)



ecm_qt_declare_logging_category(webengineviewer_adblockplugin HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME org.kde.pim.adblockinterceptor
    DESCRIPTION "kdepim-addons (adblock interceptor)"
    OLD_CATEGORY_NAMES log_adblockinterceptor
    EXPORT KDEPIMADDONS
)

target_link_libraries(webengineviewer_adblockplugin
    KPim6::MessageViewer
    KF6::I18n
    Qt::WebEngineWidgets
    KPim6::WebEngineViewer

    adblockplugin
)
target_include_directories(webengineviewer_adblockplugin PRIVATE
    ${CMAKE_BINARY_DIR}/cargo/build/${Rust_CARGO_TARGET}/cxxbridge/webengineviewer-adblock/src/)

if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()
