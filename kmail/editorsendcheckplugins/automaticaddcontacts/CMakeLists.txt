set(kmail_automaticaddcontactseditorplugin_SRCS
    automaticaddcontactsinterface.cpp
    automaticaddcontactsplugin.cpp
    automaticaddcontactsconfigurewidget.cpp
    automaticaddcontactsjob.cpp
    automaticaddcontactstabwidget.cpp
    automaticaddcontactsconfiguretab.cpp
    )

ecm_qt_declare_logging_category(kmail_automaticaddcontactseditorplugin_SRCS HEADER automaticaddcontactsplugin_debug.h IDENTIFIER KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG CATEGORY_NAME log_kmail_automaticaddcontactsplugin)

add_library(kmail_automaticaddcontactseditorplugin MODULE ${kmail_automaticaddcontactseditorplugin_SRCS})

target_link_libraries(kmail_automaticaddcontactseditorplugin
    KF5::IconThemes KF5::MessageComposer KF5::I18n KF5::PimCommon
    )

install(TARGETS kmail_automaticaddcontactseditorplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kmail)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

