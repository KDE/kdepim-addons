set(kmail_automaticaddcontactseditorplugin_SRCS
    automaticaddcontactsinterface.cpp
    automaticaddcontactsplugin.cpp
    automaticaddcontactsconfigurewidget.cpp
    automaticaddcontactsjob.cpp
    automaticaddcontactstabwidget.cpp
    automaticaddcontactsconfiguretab.cpp
    automaticaddcontactsconfiguredialog.cpp
    )

ecm_qt_declare_logging_category(kmail_automaticaddcontactseditorplugin_SRCS HEADER automaticaddcontactsplugin_debug.h IDENTIFIER KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_automaticaddcontactsplugin)

kcoreaddons_add_plugin(kmail_automaticaddcontactseditorplugin JSON kmail_automaticaddcontactsplugin.json SOURCES
    ${kmail_automaticaddcontactseditorplugin_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(kmail_automaticaddcontactseditorplugin
	KF5::IconThemes KF5::MessageComposer KF5::I18n KF5::PimCommon KF5::AkonadiContact KF5::AkonadiCore
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

