kcoreaddons_add_plugin(messageviewer_createtodoplugin INSTALL_NAMESPACE messageviewer/viewerplugin)
target_sources(messageviewer_createtodoplugin PRIVATE
    viewerplugincreatetodo.cpp
    viewerplugincreatetodointerface.cpp
    todoedit.cpp
    createtodojob.cpp
    )
ecm_qt_declare_logging_category(messageviewer_createtodoplugin HEADER createtodoplugin_debug.h IDENTIFIER CREATETODOPLUGIN_LOG CATEGORY_NAME org.kde.pim.createtodoplugin
    DESCRIPTION "kdepim-addons (create todo plugin)"
    OLD_CATEGORY_NAMES log_createtodoplugin
    EXPORT KDEPIMADDONS
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_createtodoplugin PROPERTIES UNITY_BUILD ON)
endif()


target_link_libraries(messageviewer_createtodoplugin
    KF5::MessageViewer KF5::XmlGui KF5::CalendarCore KF5::IncidenceEditor KF5::AkonadiWidgets KF5::CalendarSupport
    )

