set(messageviewer_webengineurlinterceptor_adblock_SRCS
    adblockinterceptorinterface.cpp
    adblockpluginulrinterceptor.cpp
    )

add_library(messageviewer_adblockplugin MODULE ${messageviewer_webengineurlinterceptor_adblock_SRCS})

target_link_libraries(messageviewer_adblockplugin
    KF5::MessageViewer
    )

install(TARGETS messageviewer_adblockplugin DESTINATION ${PLUGIN_INSTALL_DIR}/messageviewer)

