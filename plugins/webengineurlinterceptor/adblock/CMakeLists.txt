# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(webengineviewer_adblockplugin INSTALL_NAMESPACE pim6/webengineviewer/urlinterceptor)
target_sources(webengineviewer_adblockplugin PRIVATE
    adblockinterceptorinterface.cpp
    adblockpluginurlinterceptor.cpp
    adblockinterceptorinterface.h
    adblockpluginurlinterceptor.h
    adblockmanager.h
    adblockmanager.cpp
    )

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

target_include_directories(webengineviewer_adblockplugin PRIVATE
    ${CMAKE_BINARY_DIR}/cargo/build/${Rust_CARGO_TARGET}/cxxbridge/webengineviewer-adblock/src/)


ecm_qt_declare_logging_category(webengineviewer_adblockplugin HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME org.kde.pim.adblockinterceptor
    DESCRIPTION "kdepim-addons (adblock interceptor)"
    OLD_CATEGORY_NAMES log_adblockinterceptor
    EXPORT KDEPIMADDONS
    )

kconfig_add_kcfg_files(webengineviewer_adblockplugin
    settings/globalsettings_webengineurlinterceptoradblock.kcfgc
    )

target_link_libraries(webengineviewer_adblockplugin
    KPim6::MessageViewer
    KF6::I18n
    Qt::WebEngineWidgets
    KPim6::WebEngineViewer
    webengineviewer-adblock
    )
