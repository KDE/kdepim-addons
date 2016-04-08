set(webengineviewer_webengineurlinterceptor_adblock_SRCS
    adblockinterceptorinterface.cpp
    adblockpluginurlinterceptor.cpp
    )

ecm_qt_declare_logging_category(webengineviewer_webengineurlinterceptor_adblock_SRCS HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME log_adblockinterceptor)


add_library(webengineviewer_adblockplugin MODULE ${webengineviewer_webengineurlinterceptor_adblock_SRCS})

target_link_libraries(webengineviewer_adblockplugin
    KF5::MessageViewer
    Qt5::WebEngine
    Qt5::WebEngineWidgets
    KF5::ItemViews
    adblocklibprivate
    KF5::KIOWidgets
    KF5::XmlGui
    KF5::I18n
    KF5::WebEngineViewer
    )

install(TARGETS webengineviewer_adblockplugin DESTINATION ${PLUGIN_INSTALL_DIR}/webengineviewer)

if(BUILD_TESTING)
   add_subdirectory(tests)
   add_subdirectory(autotests)
endif()
add_subdirectory(lib)
