set(kmail_confirmaddresseditorplugin_SRCS
    confirmaddressinterface.cpp
    confirmaddressplugin.cpp
    confirmaddressconfigurewidget.cpp
    confirmaddressdialog.cpp
    )

ecm_qt_declare_logging_category(kmail_confirmaddresseditorplugin_SRCS HEADER confirmaddressplugin_debug.h IDENTIFIER KMAIL_EDITOR_CONFIRMADDRESS_PLUGIN_LOG CATEGORY_NAME log_kmail_confirmaddressplugin)

add_library(kmail_confirmaddresseditorplugin MODULE ${kmail_confirmaddresseditorplugin_SRCS})

target_link_libraries(kmail_confirmaddresseditorplugin
    KF5::IconThemes KF5::MessageComposer KF5::I18n
    )

install(TARGETS kmail_confirmaddresseditorplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kmail)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

