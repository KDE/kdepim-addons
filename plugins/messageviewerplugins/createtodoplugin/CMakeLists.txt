set(messageviewer_createtodoplugin_SRCS
    viewerplugincreatetodo.cpp
    viewerplugincreatetodointerface.cpp
    todoedit.cpp
    createtodojob.cpp
)
ecm_qt_declare_logging_category(messageviewer_createtodoplugin_SRCS HEADER createtodoplugin_debug.h IDENTIFIER CREATETODOPLUGIN_LOG CATEGORY_NAME log_createtodoplugin)

kcoreaddons_add_plugin(messageviewer_createtodoplugin JSON messageviewer_createtodoplugin.json SOURCES
    ${messageviewer_createtodoplugin_SRCS} INSTALL_NAMESPACE messageviewer)


target_link_libraries(messageviewer_createtodoplugin
  KF5::MessageViewer KF5::XmlGui KF5::CalendarCore KF5::IncidenceEditor
)

