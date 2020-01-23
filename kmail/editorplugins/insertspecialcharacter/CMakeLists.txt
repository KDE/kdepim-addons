set(kmail_insertspecialcharactereditorplugin_SRCS
    insertspecialcharacterplugineditor.cpp
    insertspecialcharacterplugineditorinterface.cpp
)

kcoreaddons_add_plugin(kmail_insertspecialcharactereditorplugin JSON kmail_insertspecialcharactereditorplugin.json SOURCES
    ${kmail_insertspecialcharactereditorplugin_SRCS} INSTALL_NAMESPACE kmail/plugineditor)

target_link_libraries(kmail_insertspecialcharactereditorplugin
  KF5::MessageComposer KF5::XmlGui KF5::I18n
)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

