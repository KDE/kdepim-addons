set(messageviewer_createtodoplugin_SRCS
    viewerplugincreatetodo.cpp
    viewerplugincreatetodointerface.cpp
    todoedit.cpp
    createtodojob.cpp
)
ecm_qt_declare_logging_category(messageviewer_createtodoplugin_SRCS HEADER createtodoplugin_debug.h IDENTIFIER CREATETODOPLUGIN_LOG CATEGORY_NAME log_createtodoplugin)
add_library(messageviewer_createtodoplugin MODULE ${messageviewer_createtodoplugin_SRCS})

target_link_libraries(messageviewer_createtodoplugin
  KF5::MessageViewer KF5::XmlGui KF5::CalendarCore KF5::IncidenceEditor
)

install(TARGETS messageviewer_createtodoplugin DESTINATION ${PLUGIN_INSTALL_DIR}/messageviewer)
 
