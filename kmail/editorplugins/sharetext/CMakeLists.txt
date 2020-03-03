set(kmail_sharetexteditorplugin_SRCS
    sharetextplugineditor.cpp
    sharetextplugineditorinterface.cpp
    sharetextpurposemenuwidget.cpp
)

if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(kmail_sharetexteditorplugin_SRCS HEADER sharetexteditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_SHARETEXT_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_sharetexteditorplugin)
else()
    ecm_qt_declare_logging_category(kmail_sharetexteditorplugin_SRCS HEADER sharetexteditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_SHARETEXT_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_sharetexteditorplugin
        DESCRIPTION "kdepim-addons (share text editor plugin)"
        EXPORT KDEPIMADDONS
    )
endif()


kcoreaddons_add_plugin(kmail_sharetexteditorplugin JSON kmail_sharetexteditorplugin.json SOURCES
    ${kmail_sharetexteditorplugin_SRCS} INSTALL_NAMESPACE kmail/plugineditor)

target_link_libraries(kmail_sharetexteditorplugin
  KF5::MessageComposer KF5::XmlGui KF5::I18n
)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

