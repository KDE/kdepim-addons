set(messageviewer_createnoteplugin_SRCS
    viewerplugincreatenote.cpp
    viewerplugincreatenoteinterface.cpp
    noteedit.cpp
    createnotejob.cpp
)
ecm_qt_declare_logging_category(messageviewer_createnoteplugin_SRCS HEADER createnoteplugin_debug.h IDENTIFIER CREATENOTEPLUGIN_LOG CATEGORY_NAME org.kde.pim.createnoteplugin)

kcoreaddons_add_plugin(messageviewer_createnoteplugin JSON messageviewer_createnoteplugin.json SOURCES
    ${messageviewer_createnoteplugin_SRCS} INSTALL_NAMESPACE messageviewer)


target_link_libraries(messageviewer_createnoteplugin
  KF5::MessageViewer KF5::XmlGui KF5::CalendarCore KF5::AkonadiNotes KF5::IncidenceEditor
)
 
