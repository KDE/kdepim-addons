set(kmail_checkbeforesendeditorplugin_SRCS
    checkbeforesendplugin.cpp
    )

ecm_qt_declare_logging_category(kmail_checkbeforesendeditorplugin_SRCS HEADER checkbeforesendplugin_debug.h IDENTIFIER KMAIL_EDITOR_checkbeforesend_PLUGIN_LOG CATEGORY_NAME log_kmail_checkbeforesendplugin)

add_library(kmail_checkbeforesendeditorplugin MODULE ${kmail_checkbeforesendeditorplugin_SRCS})

target_link_libraries(kmail_checkbeforesendeditorplugin
    KF5::IconThemes KF5::MessageComposer KF5::I18n
    )

install(TARGETS kmail_checkbeforesendeditorplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kmail)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
