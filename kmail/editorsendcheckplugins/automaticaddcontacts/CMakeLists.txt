set(kmail_automaticaddcontactseditorplugin_SRCS
    automaticaddcontactsinterface.cpp
    automaticaddcontactsplugin.cpp
    automaticaddcontactsconfigurewidget.cpp
    automaticaddcontactsjob.cpp
    automaticaddcontactstabwidget.cpp
    automaticaddcontactsconfiguretab.cpp
    automaticaddcontactsconfiguredialog.cpp
    )

if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(kmail_automaticaddcontactseditorplugin_SRCS HEADER automaticaddcontactsplugin_debug.h IDENTIFIER KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_automaticaddcontactsplugin)
else()
    ecm_qt_declare_logging_category(kmail_automaticaddcontactseditorplugin_SRCS HEADER automaticaddcontactsplugin_debug.h IDENTIFIER KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_automaticaddcontactsplugin
        DESCRIPTION "kdepim-addons (Automatic add contacts plugin)"
        OLD_CATEGORY_NAMES log_kmail_automaticaddcontactsplugin
        EXPORT KDEPIMADDONS
    )
endif()


kcoreaddons_add_plugin(kmail_automaticaddcontactseditorplugin JSON kmail_automaticaddcontactsplugin.json SOURCES
    ${kmail_automaticaddcontactseditorplugin_SRCS} INSTALL_NAMESPACE kmail/plugincheckbeforesend)

target_link_libraries(kmail_automaticaddcontactseditorplugin
	KF5::MessageComposer KF5::I18n KF5::PimCommon KF5::AkonadiContact KF5::AkonadiCore
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

