set(messageviewer_expandurlplugin_SRCS
    viewerpluginexpandurl.cpp
    viewerpluginexpandurlinterface.cpp
)

ecm_qt_declare_logging_category(messageviewer_expandurlplugin_SRCS HEADER expandurlplugin_debug.h IDENTIFIER EXPANDURLPLUGIN_LOG CATEGORY_NAME log_expandurlplugin)

add_library(messageviewer_expandurlplugin MODULE ${messageviewer_expandurlplugin_SRCS})

target_link_libraries(messageviewer_expandurlplugin
  KF5::MessageViewer KF5::XmlGui KF5::Libkdepim KF5::I18n
)

install(TARGETS messageviewer_expandurlplugin DESTINATION ${PLUGIN_INSTALL_DIR}/messageviewer)
 
