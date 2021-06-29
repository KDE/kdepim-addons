kcoreaddons_add_plugin(messageviewer_createnoteplugin INSTALL_NAMESPACE messageviewer/viewerplugin)
target_sources(messageviewer_createnoteplugin PRIVATE
    viewerplugincreatenote.cpp
    viewerplugincreatenoteinterface.cpp
    noteedit.cpp
    createnotejob.cpp
    )
ecm_qt_declare_logging_category(messageviewer_createnoteplugin HEADER createnoteplugin_debug.h IDENTIFIER CREATENOTEPLUGIN_LOG CATEGORY_NAME org.kde.pim.createnoteplugin
    DESCRIPTION "kdepim-addons (create note plugin)"
    OLD_CATEGORY_NAMES log_createnoteplugin
    EXPORT KDEPIMADDONS
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_createnoteplugin PROPERTIES UNITY_BUILD ON)
endif()


target_link_libraries(messageviewer_createnoteplugin
    KF5::MessageViewer KF5::XmlGui KF5::CalendarCore KF5::AkonadiNotes KF5::IncidenceEditor KF5::AkonadiWidgets
    )

