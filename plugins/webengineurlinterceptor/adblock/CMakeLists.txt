kcoreaddons_add_plugin(webengineviewer_adblockplugin INSTALL_NAMESPACE webengineviewer/urlinterceptor)
target_sources(webengineviewer_adblockplugin PRIVATE
    adblockinterceptorinterface.cpp
    adblockpluginurlinterceptor.cpp
    )

ecm_qt_declare_logging_category(webengineviewer_adblockplugin HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME org.kde.pim.adblockinterceptor
    DESCRIPTION "kdepim-addons (adblock interceptor)"
    OLD_CATEGORY_NAMES log_adblockinterceptor
    EXPORT KDEPIMADDONS
    )



target_link_libraries(webengineviewer_adblockplugin
    KF5::MessageViewer
    Qt::WebEngine
    Qt::WebEngineWidgets
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
