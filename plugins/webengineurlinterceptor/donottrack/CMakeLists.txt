# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set(webengineviewer_webengineurlinterceptor_donottrack_SRCS
    donottrackinterceptorinterface.cpp
    donottrackpluginurlinterceptor.cpp
    donottrackinterceptorinterface.h
    donottrackpluginurlinterceptor.h
    )

ecm_qt_declare_logging_category(webengineviewer_webengineurlinterceptor_donottrack_SRCS HEADER donottrackinterceptor_debug.h IDENTIFIER DONOTTRACKINTERCEPTOR_LOG CATEGORY_NAME org.kde.pim.donottrackinterceptor
    DESCRIPTION "kdepim-addons (do not track interceptor)"
    OLD_CATEGORY_NAMES log_donottrackinterceptor
    EXPORT KDEPIMADDONS
    )


kconfig_add_kcfg_files(webengineviewer_webengineurlinterceptor_donottrack_SRCS
    settings/donottracksettings.kcfgc
    )


kcoreaddons_add_plugin(webengineviewer_donottrackplugin SOURCES
    ${webengineviewer_webengineurlinterceptor_donottrack_SRCS} INSTALL_NAMESPACE pim6/webengineviewer/urlinterceptor)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(webengineviewer_donottrackplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(webengineviewer_donottrackplugin
    
    Qt::WebEngineWidgets
    KPim6::WebEngineViewer
    KF6::ConfigGui
    KF6::CoreAddons
    )
if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
