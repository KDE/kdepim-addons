set(kmail_rot13editorplugin_SRCS
    rot13plugineditor.cpp
    rot13plugineditorinterface.cpp
    rot13job.cpp
)

kcoreaddons_add_plugin(kmail_rot13editorplugin JSON kmail_rot13editorplugin.json SOURCES
    ${kmail_rot13editorplugin_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(kmail_rot13editorplugin
  KF5::IconThemes KF5::MessageComposer KF5::XmlGui KF5::I18n
)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

