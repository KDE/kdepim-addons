set(kmail_externalcomposereditorplugin_SRCS
    externalcomposerplugineditor.cpp
    externalcomposerplugineditorinterface.cpp
)

kcoreaddons_add_plugin(kmail_externalcomposereditorplugin JSON kmail_externalcomposereditorplugin.json SOURCES
    ${kmail_externalcomposereditorplugin_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(kmail_externalcomposereditorplugin
  KF5::IconThemes KF5::MessageComposer KF5::XmlGui KF5::I18n
)

#if(BUILD_TESTING)
#   add_subdirectory(autotests)
#endif()

