set(messageviewer_createnoteplugin_SRCS
    viewerplugincreatenote.cpp
    viewerplugincreatenoteinterface.cpp
    noteedit.cpp
    createnotejob.cpp
    )
ecm_qt_declare_logging_category(messageviewer_createnoteplugin_SRCS HEADER createnoteplugin_debug.h IDENTIFIER CREATENOTEPLUGIN_LOG CATEGORY_NAME org.kde.pim.createnoteplugin
    DESCRIPTION "kdepim-addons (create note plugin)"
    OLD_CATEGORY_NAMES log_createnoteplugin
    EXPORT KDEPIMADDONS
    )


kcoreaddons_add_plugin(messageviewer_createnoteplugin JSON messageviewer_createnoteplugin.json SOURCES
    ${messageviewer_createnoteplugin_SRCS} INSTALL_NAMESPACE messageviewer/viewerplugin)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_createnoteplugin PROPERTIES UNITY_BUILD ON)
endif()


target_link_libraries(messageviewer_createnoteplugin
    KF5::MessageViewer KF5::XmlGui KF5::CalendarCore KF5::AkonadiNotes KF5::IncidenceEditor KF5::AkonadiWidgets
    )

