set(messageviewer_webengineurlinterceptor_adblock_SRCS
    adblockinterceptorinterface.cpp
    adblockpluginurlinterceptor.cpp
    adblockpluginurlinterceptorconfigurewidget.cpp
    adblockblockableitemsdialog.cpp
    adblockblockableitemswidget.cpp
    )

ecm_qt_declare_logging_category(messageviewer_webengineurlinterceptor_adblock_SRCS HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME log_adblockinterceptor)


add_library(messageviewer_adblockplugin MODULE ${messageviewer_webengineurlinterceptor_adblock_SRCS})

target_link_libraries(messageviewer_adblockplugin
    KF5::MessageViewer
    Qt5::WebEngine
    Qt5::WebEngineWidgets
    KF5::ItemViews
    adblocklibprivate
    KF5::KIOWidgets
    KF5::XmlGui
    )

install(TARGETS messageviewer_adblockplugin DESTINATION ${PLUGIN_INSTALL_DIR}/messageviewer)

if(BUILD_TESTING)
   add_subdirectory(tests)
   add_subdirectory(autotests)
endif()
add_subdirectory(lib)
