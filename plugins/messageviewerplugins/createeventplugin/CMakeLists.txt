set(messageviewer_createeventplugin_SRCS
    viewerplugincreateevent.cpp
    viewerplugincreateeventinterface.cpp
    eventedit.cpp
    eventdatetimewidget.cpp
    createeventjob.cpp
)

ecm_qt_declare_logging_category(messageviewer_createeventplugin_SRCS HEADER createeventplugin_debug.h IDENTIFIER CREATEEVENTPLUGIN_LOG CATEGORY_NAME org.kde.pim.createeventplugin)

kcoreaddons_add_plugin(messageviewer_createeventplugin JSON messageviewer_createeventplugin.json SOURCES
    ${messageviewer_createeventplugin_SRCS} INSTALL_NAMESPACE messageviewer)


target_link_libraries(messageviewer_createeventplugin
        KF5::MessageViewer KF5::XmlGui KF5::CalendarCore KF5::IncidenceEditor KF5::AkonadiWidgets KF5::CalendarSupport
)

