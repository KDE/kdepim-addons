set(messageviewer_expandurlplugin_SRCS
    viewerpluginexpandurl.cpp
    viewerpluginexpandurlinterface.cpp
)

add_library(messageviewer_expandurlplugin MODULE ${messageviewer_expandurlplugin_SRCS})

target_link_libraries(messageviewer_expandurlplugin
  KF5::MessageViewer KF5::XmlGui KF5::Libkdepim KF5::I18n
)

install(TARGETS messageviewer_expandurlplugin DESTINATION ${PLUGIN_INSTALL_DIR}/messageviewer)
 
