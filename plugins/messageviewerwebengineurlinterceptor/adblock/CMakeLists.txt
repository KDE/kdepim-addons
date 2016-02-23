set(messageviewer_webengineurlinterceptor_adblock_SRCS
    adblockinterceptorinterface.cpp
    adblockpluginurlinterceptor.cpp
    adblockpluginurlinterceptorconfigurewidget.cpp
    )

add_library(messageviewer_adblockplugin MODULE ${messageviewer_webengineurlinterceptor_adblock_SRCS})

target_link_libraries(messageviewer_adblockplugin
    KF5::MessageViewer
    Qt5::WebEngine Qt5::WebEngineWidgets
    adblocklibprivate
    )

install(TARGETS messageviewer_adblockplugin DESTINATION ${PLUGIN_INSTALL_DIR}/messageviewer)

add_subdirectory(autotests)
add_subdirectory(lib)
