set(messageviewer_webengineurlinterceptor_donottrack_SRCS
    donottrackinterceptorinterface.cpp
    donottrackpluginurlinterceptor.cpp
    )

add_library(messageviewer_donottrackplugin MODULE ${messageviewer_webengineurlinterceptor_donottrack_SRCS})

target_link_libraries(messageviewer_donottrackplugin
    KF5::MessageViewer
    Qt5::WebEngine
    Qt5::WebEngineWidgets
    )

install(TARGETS messageviewer_donottrackplugin DESTINATION ${PLUGIN_INSTALL_DIR}/messageviewer)

#add_subdirectory(autotests)
