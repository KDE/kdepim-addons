kcoreaddons_add_plugin(messageviewer_createeventplugin INSTALL_NAMESPACE messageviewer/viewerplugin)
target_sources(messageviewer_createeventplugin PRIVATE
    viewerplugincreateevent.cpp
    viewerplugincreateeventinterface.cpp
    eventedit.cpp
    eventdatetimewidget.cpp
    createeventjob.cpp
    )

ecm_qt_declare_logging_category(messageviewer_createeventplugin HEADER createeventplugin_debug.h IDENTIFIER CREATEEVENTPLUGIN_LOG CATEGORY_NAME org.kde.pim.createeventplugin
    DESCRIPTION "kdepim-addons (create event plugin)"
    OLD_CATEGORY_NAMES log_createeventplugin
    EXPORT KDEPIMADDONS
    )



if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_createeventplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_createeventplugin
    KF5::MessageViewer KF5::XmlGui KF5::CalendarCore KF5::IncidenceEditor KF5::AkonadiWidgets KF5::CalendarSupport
    )

