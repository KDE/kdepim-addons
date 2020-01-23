set(webengineviewer_webengineurlinterceptor_adblock_SRCS
    adblockinterceptorinterface.cpp
    adblockpluginurlinterceptor.cpp
    )

ecm_qt_declare_logging_category(webengineviewer_webengineurlinterceptor_adblock_SRCS HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME org.kde.pim.adblockinterceptor)


kcoreaddons_add_plugin(webengineviewer_adblockplugin JSON messageviewer_adblockurlinterceptor.json SOURCES
    ${webengineviewer_webengineurlinterceptor_adblock_SRCS} INSTALL_NAMESPACE webengineviewer/urlinterceptor)

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

if(BUILD_TESTING)
   add_subdirectory(tests)
   add_subdirectory(autotests)
endif()
add_subdirectory(lib)
add_subdirectory(kconf_update)
