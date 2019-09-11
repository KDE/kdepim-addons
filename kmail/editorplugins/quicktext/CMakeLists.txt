if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()
set(kmail_quicktextplugin_SRCS
    quicktextplugineditor.cpp
    quicktextplugineditorinterface.cpp
    quicktextmenu.cpp
)

ecm_qt_declare_logging_category(kmail_quicktextplugin_SRCS HEADER quicktextplugin_debug.h IDENTIFIER KMAIL_EDITOR_QUICKTEXT_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_quicktextplugin)

kcoreaddons_add_plugin(kmail_quicktextplugin JSON kmail_quicktextplugin.json SOURCES
    ${kmail_quicktextplugin_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(kmail_quicktextplugin
  KF5::IconThemes KF5::MessageComposer KF5::XmlGui KF5::I18n
)
