# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(webengineviewer_adblockplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/webengineviewer/urlinterceptor)
target_sources(webengineviewer_adblockplugin PRIVATE
    adblockinterceptorinterface.cpp
    adblockpluginurlinterceptor.cpp
    adblockinterceptorinterface.h
    adblockpluginurlinterceptor.h
    )

ecm_qt_declare_logging_category(webengineviewer_adblockplugin HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME org.kde.pim.adblockinterceptor
    DESCRIPTION "kdepim-addons (adblock interceptor)"
    OLD_CATEGORY_NAMES log_adblockinterceptor
    EXPORT KDEPIMADDONS
    )



target_link_libraries(webengineviewer_adblockplugin
    KPim${KF_MAJOR_VERSION}::MessageViewer
    Qt::WebEngineWidgets
    KF${KF_MAJOR_VERSION}::ItemViews
    adblocklibprivate
    KF${KF_MAJOR_VERSION}::KIOWidgets
    KF${KF_MAJOR_VERSION}::XmlGui
    KF${KF_MAJOR_VERSION}::I18n
    KPim${KF_MAJOR_VERSION}::WebEngineViewer
    )

if(BUILD_TESTING)
    add_subdirectory(tests)
    add_subdirectory(autotests)
endif()
add_subdirectory(lib)
add_subdirectory(kconf_update)
