set(kmail_insertemaileditorplugin_SRCS
    insertemailplugineditor.cpp
    insertemailplugineditorinterface.cpp
    selectmailwidget.cpp
    selectmaildialog.cpp
)

kcoreaddons_add_plugin(kmail_insertemaileditorplugin JSON kmail_insertemaileditorplugin.json SOURCES
    ${kmail_insertemaileditorplugin_SRCS} INSTALL_NAMESPACE kmail/plugineditor)

target_link_libraries(kmail_insertemaileditorplugin
  KF5::MessageComposer KF5::XmlGui KF5::I18n KF5::AkonadiContact
)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_insertemaileditorplugin PROPERTIES UNITY_BUILD ON)
endif()

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

