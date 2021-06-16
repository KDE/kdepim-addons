kcoreaddons_add_plugin(kmail_insertspecialcharactereditorplugin JSON kmail_insertspecialcharactereditorplugin.json INSTALL_NAMESPACE kmail/plugineditor)
target_sources(kmail_insertspecialcharactereditorplugin PRIVATE
    insertspecialcharacterplugineditor.cpp
    insertspecialcharacterplugineditorinterface.cpp
)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_insertspecialcharactereditorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_insertspecialcharactereditorplugin
  KF5::MessageComposer KF5::XmlGui KF5::I18n
)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

