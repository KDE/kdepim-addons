set(kmail_changecaseeditorplugin_SRCS
    changecaseplugineditor.cpp
    changecaseplugineditorinterface.cpp
)

add_library(kmail_changecaseeditorplugin MODULE ${kmail_changecaseeditorplugin_SRCS})

target_link_libraries(kmail_changecaseeditorplugin
  KF5::IconThemes KF5::MessageComposer KF5::XmlGui
)

install(TARGETS kmail_changecaseeditorplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kmail)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

