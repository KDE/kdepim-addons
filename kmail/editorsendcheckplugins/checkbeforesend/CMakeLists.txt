include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

set(kmail_checkbeforesendeditorplugin_SRCS
    checkbeforesendplugin.cpp
    checkbeforesendinterface.cpp
    configurewidget/checkbeforesendconfigurewidget.cpp
    configurewidget/checkbeforesendconfiguredialog.cpp
    duplicateemails/checkduplicateemailsdialog.cpp
    duplicateemails/checkduplicateemailsjob.cpp
    sendattachments/checkattachmentdialog.cpp
    sendattachments/checkattachmentjob.cpp
    )

ecm_qt_declare_logging_category(kmail_checkbeforesendeditorplugin_SRCS HEADER checkbeforesendplugin_debug.h IDENTIFIER KMAIL_EDITOR_checkbeforesend_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_checkbeforesendplugin)

kcoreaddons_add_plugin(kmail_checkbeforesendeditorplugin JSON kmail_checkbeforesendplugin.json SOURCES
    ${kmail_checkbeforesendeditorplugin_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(kmail_checkbeforesendeditorplugin
    KF5::IconThemes KF5::MessageComposer KF5::I18n
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
