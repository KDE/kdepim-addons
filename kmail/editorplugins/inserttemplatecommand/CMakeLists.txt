set(kmail_inserttemplatecommandeditorplugin_SRCS
    inserttemplatecommandplugineditor.cpp
    inserttemplatecommandplugineditorinterface.cpp
)

kcoreaddons_add_plugin(kmail_inserttemplatecommandeditorplugin JSON kmail_inserttemplatecommandeditorplugin.json SOURCES
    ${kmail_inserttemplatecommandeditorplugin_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(kmail_inserttemplatecommandeditorplugin
  KF5::IconThemes KF5::MessageComposer KF5::XmlGui KF5::I18n
)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

