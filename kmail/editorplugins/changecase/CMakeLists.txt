set(kmail_changecaseeditorplugin_SRCS
    changecaseplugineditor.cpp
    changecaseplugineditorinterface.cpp
)

ecm_qt_declare_logging_category(kmail_changecaseeditorplugin_SRCS HEADER changecaseeditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_CHANGECASE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_changecaseeditorplugin)

kcoreaddons_add_plugin(kmail_changecaseeditorplugin JSON kmail_changecaseeditorplugin.json SOURCES
    ${kmail_changecaseeditorplugin_SRCS} INSTALL_NAMESPACE kmail/plugineditor)

target_link_libraries(kmail_changecaseeditorplugin
  KF5::MessageComposer KF5::XmlGui KF5::I18n
)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

