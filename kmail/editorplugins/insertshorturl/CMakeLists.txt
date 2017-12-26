set(kmail_insertshorturleditorplugin_SRCS
    insertshorturlplugineditor.cpp
    insertshorturlplugineditorinterface.cpp
)

kcoreaddons_add_plugin(kmail_insertshorturleditorplugin JSON kmail_insertshorturleditorplugin.json SOURCES
    ${kmail_insertshorturleditorplugin_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(kmail_insertshorturleditorplugin
  KF5::IconThemes KF5::MessageComposer KF5::XmlGui KF5::I18n KF5::AkonadiContact
)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()


