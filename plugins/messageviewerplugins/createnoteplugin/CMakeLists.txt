set(messageviewer_createnoteplugin_SRCS
    viewerplugincreatenote.cpp
    viewerplugincreatenoteinterface.cpp
    noteedit.cpp
    createnotejob.cpp
)
ecm_qt_declare_logging_category(messageviewer_createnoteplugin_SRCS HEADER createnoteplugin_debug.h IDENTIFIER CREATENOTEPLUGIN_LOG CATEGORY_NAME log_createnoteplugin)
add_library(messageviewer_createnoteplugin MODULE ${messageviewer_createnoteplugin_SRCS})

target_link_libraries(messageviewer_createnoteplugin
  KF5::MessageViewer KF5::XmlGui KF5::CalendarCore KF5::AkonadiNotes KF5::IncidenceEditor
)

install(TARGETS messageviewer_createnoteplugin DESTINATION ${PLUGIN_INSTALL_DIR}/messageviewer)
 
