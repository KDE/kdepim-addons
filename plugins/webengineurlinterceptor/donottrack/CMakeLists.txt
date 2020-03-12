set(webengineviewer_webengineurlinterceptor_donottrack_SRCS
    donottrackinterceptorinterface.cpp
    donottrackpluginurlinterceptor.cpp
    )

ecm_qt_declare_logging_category(webengineviewer_webengineurlinterceptor_donottrack_SRCS HEADER donottrackinterceptor_debug.h IDENTIFIER DONOTTRACKINTERCEPTOR_LOG CATEGORY_NAME org.kde.pim.donottrackinterceptor
    DESCRIPTION "kdepim-addons (do not track interceptor)"
    OLD_CATEGORY_NAMES log_donottrackinterceptor
    EXPORT KDEPIMADDONS
    )


kconfig_add_kcfg_files(webengineviewer_webengineurlinterceptor_donottrack_SRCS
    settings/donottracksettings.kcfgc
    )


kcoreaddons_add_plugin(webengineviewer_donottrackplugin JSON messageviewer_donottrackurlinterceptor.json SOURCES
    ${webengineviewer_webengineurlinterceptor_donottrack_SRCS} INSTALL_NAMESPACE webengineviewer/urlinterceptor)

target_link_libraries(webengineviewer_donottrackplugin
    Qt5::WebEngine
    Qt5::WebEngineWidgets
    KF5::WebEngineViewer
    KF5::ConfigGui
    KF5::CoreAddons
    )
if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
