set(messageviewer_createtodoplugin_SRCS
    viewerplugincreatetodo.cpp
    viewerplugincreatetodointerface.cpp
    todoedit.cpp
    createtodojob.cpp
)
if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(messageviewer_createtodoplugin_SRCS HEADER createtodoplugin_debug.h IDENTIFIER CREATETODOPLUGIN_LOG CATEGORY_NAME org.kde.pim.createtodoplugin)
else()
    ecm_qt_declare_logging_category(messageviewer_createtodoplugin_SRCS HEADER createtodoplugin_debug.h IDENTIFIER CREATETODOPLUGIN_LOG CATEGORY_NAME org.kde.pim.createtodoplugin
        DESCRIPTION "kdepim-addons (create todo plugin)"
        OLD_CATEGORY_NAMES log_createtodoplugin
        EXPORT KDEPIMADDONS
        )
endif()


kcoreaddons_add_plugin(messageviewer_createtodoplugin JSON messageviewer_createtodoplugin.json SOURCES
    ${messageviewer_createtodoplugin_SRCS} INSTALL_NAMESPACE messageviewer/viewerplugin)


target_link_libraries(messageviewer_createtodoplugin
        KF5::MessageViewer KF5::XmlGui KF5::CalendarCore KF5::IncidenceEditor KF5::AkonadiWidgets KF5::CalendarSupport
)

