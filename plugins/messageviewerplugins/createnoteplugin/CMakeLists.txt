set(messageviewer_createnoteplugin_SRCS
    viewerplugincreatenote.cpp
    viewerplugincreatenoteinterface.cpp
    noteedit.cpp
    createnotejob.cpp
)
if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(messageviewer_createnoteplugin_SRCS HEADER createnoteplugin_debug.h IDENTIFIER CREATENOTEPLUGIN_LOG CATEGORY_NAME org.kde.pim.createnoteplugin)
else()
    ecm_qt_declare_logging_category(messageviewer_createnoteplugin_SRCS HEADER createnoteplugin_debug.h IDENTIFIER CREATENOTEPLUGIN_LOG CATEGORY_NAME org.kde.pim.createnoteplugin
        DESCRIPTION "kdepim-addons (create note plugin)"
        OLD_CATEGORY_NAMES log_createnoteplugin
        EXPORT KDEPIMADDONS
        )
endif()


kcoreaddons_add_plugin(messageviewer_createnoteplugin JSON messageviewer_createnoteplugin.json SOURCES
    ${messageviewer_createnoteplugin_SRCS} INSTALL_NAMESPACE messageviewer/viewerplugin)


target_link_libraries(messageviewer_createnoteplugin
	KF5::MessageViewer KF5::XmlGui KF5::CalendarCore KF5::AkonadiNotes KF5::IncidenceEditor KF5::AkonadiWidgets
)
 
