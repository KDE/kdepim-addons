kcoreaddons_add_plugin(kmail_autocorrectioneditorplugin JSON kmail_autocorrectioneditorplugin.json
     INSTALL_NAMESPACE kmail/plugineditor)
target_sources(kmail_autocorrectioneditorplugin PRIVATE
    autocorrectionplugineditor.cpp
    autocorrectionplugineditorinterface.cpp
    )


target_link_libraries(kmail_autocorrectioneditorplugin
    KF5::MessageComposer KF5::XmlGui KF5::I18n
    )
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_autocorrectioneditorplugin PROPERTIES UNITY_BUILD ON)
endif()

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

