set(webengineviewer_webengineurlinterceptor_donottrack_SRCS
    donottrackinterceptorinterface.cpp
    donottrackpluginurlinterceptor.cpp
    )

ecm_qt_declare_logging_category(webengineviewer_webengineurlinterceptor_donottrack_SRCS HEADER donottrackinterceptor_debug.h IDENTIFIER DONOTTRACKINTERCEPTOR_LOG CATEGORY_NAME log_donottrackinterceptor)

kconfig_add_kcfg_files(webengineviewer_webengineurlinterceptor_donottrack_SRCS
  settings/donottrack.kcfgc
)


add_library(webengineviewer_donottrackplugin MODULE ${webengineviewer_webengineurlinterceptor_donottrack_SRCS})

target_link_libraries(webengineviewer_donottrackplugin
    Qt5::WebEngine
    Qt5::WebEngineWidgets
    KF5::WebEngineViewer
    KF5::ConfigGui
    KF5::CoreAddons
    )

install(TARGETS webengineviewer_donottrackplugin DESTINATION ${PLUGIN_INSTALL_DIR}/webengineviewer)

add_subdirectory(autotests)
