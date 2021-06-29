kcoreaddons_add_plugin(kmail_externalcomposereditorplugin  INSTALL_NAMESPACE kmail/plugineditorinit)
target_sources(kmail_externalcomposereditorplugin PRIVATE
    externalcomposerplugineditor.cpp
    externalcomposerplugineditorinterface.cpp
    externalcomposerconfiguredialog.cpp
    externalcomposerconfigurewidget.cpp
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_externalcomposereditorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_externalcomposereditorplugin
    KF5::MessageComposer KF5::XmlGui KF5::I18n KF5::KIOWidgets
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

