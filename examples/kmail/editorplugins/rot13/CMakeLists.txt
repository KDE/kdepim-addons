set(kmail_rot13editorplugin_SRCS
    rot13plugineditor.cpp
    rot13plugineditorinterface.cpp
    rot13job.cpp
)

add_library(kmail_rot13editorplugin MODULE ${kmail_rot13editorplugin_SRCS})

target_link_libraries(kmail_rot13editorplugin
  KF5::IconThemes KF5::MessageComposer KF5::XmlGui KF5::I18n
)

# Enable to install the example plugin
#install(TARGETS kmail_rot13editorplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kmail)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

