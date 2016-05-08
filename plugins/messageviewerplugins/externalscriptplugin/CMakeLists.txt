set(messageviewer_externalscriptplugin_SRCS
    viewerpluginexternalscript.cpp  
    viewerpluginexternalscriptinterface.cpp
    viewerpluginexternalscriptmanager.cpp
    viewerpluginexternalscriptinfo.cpp
    viewerpluginexternalscriptsloadjob.cpp
)

ecm_qt_declare_logging_category(messageviewer_externalscriptplugin_SRCS HEADER externalscriptplugin_debug.h IDENTIFIER EXTERNALSCRIPTPLUGIN_LOG CATEGORY_NAME log_externalscriptplugin)
add_library(messageviewer_externalscriptplugin MODULE ${messageviewer_externalscriptplugin_SRCS})

target_link_libraries(messageviewer_externalscriptplugin
  KF5::MessageViewer KF5::XmlGui KF5::I18n
)

install(TARGETS messageviewer_externalscriptplugin DESTINATION ${PLUGIN_INSTALL_DIR}/messageviewer)
 
