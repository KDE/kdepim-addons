set(kmail_confirmaddresseditorplugin_SRCS
    confirmaddressinterface.cpp
    confirmaddressplugin.cpp
    confirmaddressconfigurewidget.cpp
    confirmaddressdialog.cpp
    confirmaddresswidget.cpp
    confirmaddressconfiguretabwidget.cpp
    confirmaddressconfiguretab.cpp
    confirmaddresscheckjob.cpp    
    )

ecm_qt_declare_logging_category(kmail_confirmaddresseditorplugin_SRCS HEADER confirmaddressplugin_debug.h IDENTIFIER KMAIL_EDITOR_CONFIRMADDRESS_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_confirmaddressplugin)

kcoreaddons_add_plugin(kmail_confirmaddresseditorplugin JSON kmail_confirmaddressplugin.json SOURCES
    ${kmail_confirmaddresseditorplugin_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(kmail_confirmaddresseditorplugin
    KF5::IconThemes KF5::MessageComposer KF5::I18n KF5::PimCommon
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

