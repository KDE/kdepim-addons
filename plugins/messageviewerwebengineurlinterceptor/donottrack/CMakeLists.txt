set(messageviewer_webengineurlinterceptor_donottrack_SRCS
    donottrackinterceptorinterface.cpp
    donottrackpluginurlinterceptor.cpp
    )

ecm_qt_declare_logging_category(messageviewer_webengineurlinterceptor_donottrack_SRCS HEADER donottrackinterceptor_debug.h IDENTIFIER DONOTTRACKINTERCEPTOR_LOG CATEGORY_NAME log_donottrackinterceptor)

kconfig_add_kcfg_files(messageviewer_webengineurlinterceptor_donottrack_SRCS
  settings/donottrack.kcfgc
)


add_library(messageviewer_donottrackplugin MODULE ${messageviewer_webengineurlinterceptor_donottrack_SRCS})

target_link_libraries(messageviewer_donottrackplugin
    Qt5::WebEngine
    Qt5::WebEngineWidgets
    KF5::WebEngineViewer
    KF5::ConfigGui
    KF5::CoreAddons
    )

install(TARGETS messageviewer_donottrackplugin DESTINATION ${PLUGIN_INSTALL_DIR}/messageviewer)

add_subdirectory(autotests)
