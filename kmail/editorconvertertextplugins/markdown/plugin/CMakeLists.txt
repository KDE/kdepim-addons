
set(kmail_markdownplugin_SRCS
    markdowninterface.cpp
    markdownplugin.cpp
    )

if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(kmail_markdownplugin_SRCS HEADER markdownplugin_debug.h IDENTIFIER KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_markdownplugin)
else()
    ecm_qt_declare_logging_category(kmail_markdownplugin_SRCS HEADER markdownplugin_debug.h IDENTIFIER KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_markdownplugin
        DESCRIPTION "kdepim-addons (kmail markdown plugin)"
        EXPORT KDEPIMADDONS
    )
endif()

kcoreaddons_add_plugin(kmail_markdownplugin JSON kmail_markdownplugin.json SOURCES
    ${kmail_markdownplugin_SRCS} INSTALL_NAMESPACE kmail/plugineditorconverttext)

target_link_libraries(kmail_markdownplugin PRIVATE
    KF5::I18n KF5::XmlGui
    kmailmarkdown
    )

