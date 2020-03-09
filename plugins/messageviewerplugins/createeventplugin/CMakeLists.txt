set(messageviewer_createeventplugin_SRCS
    viewerplugincreateevent.cpp
    viewerplugincreateeventinterface.cpp
    eventedit.cpp
    eventdatetimewidget.cpp
    createeventjob.cpp
)

if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(messageviewer_createeventplugin_SRCS HEADER createeventplugin_debug.h IDENTIFIER CREATEEVENTPLUGIN_LOG CATEGORY_NAME org.kde.pim.createeventplugin)
else()
    ecm_qt_declare_logging_category(messageviewer_createeventplugin_SRCS HEADER createeventplugin_debug.h IDENTIFIER CREATEEVENTPLUGIN_LOG CATEGORY_NAME org.kde.pim.createeventplugin
        DESCRIPTION "kdepim-addons (create event plugin)"
        OLD_CATEGORY_NAMES log_createeventplugin
        EXPORT KDEPIMADDONS
        )
endif()


kcoreaddons_add_plugin(messageviewer_createeventplugin JSON messageviewer_createeventplugin.json SOURCES
    ${messageviewer_createeventplugin_SRCS} INSTALL_NAMESPACE messageviewer/viewerplugin)


target_link_libraries(messageviewer_createeventplugin
        KF5::MessageViewer KF5::XmlGui KF5::CalendarCore KF5::IncidenceEditor KF5::AkonadiWidgets KF5::CalendarSupport
)

