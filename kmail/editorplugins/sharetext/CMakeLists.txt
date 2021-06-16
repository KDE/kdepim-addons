kcoreaddons_add_plugin(kmail_sharetexteditorplugin JSON kmail_sharetexteditorplugin.json INSTALL_NAMESPACE kmail/plugineditor)
target_sources(kmail_sharetexteditorplugin PRIVATE
    sharetextplugineditor.cpp
    sharetextplugineditorinterface.cpp
    sharetextpurposemenuwidget.cpp
    )

ecm_qt_declare_logging_category(kmail_sharetexteditorplugin HEADER sharetexteditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_SHARETEXT_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_sharetexteditorplugin
    DESCRIPTION "kdepim-addons (share text editor plugin)"
    EXPORT KDEPIMADDONS
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_sharetexteditorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_sharetexteditorplugin
    KF5::MessageComposer KF5::XmlGui KF5::I18n
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

