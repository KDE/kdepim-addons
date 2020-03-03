if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

set(languagetoolplugin_SRCS
    languagetoolplugin.cpp
    languagetoolinterface.cpp
    )

if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(languagetoolplugin_SRCS HEADER languagetoolplugin_debug.h IDENTIFIER KMAIL_EDITOR_LANGUAGETOOL_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_languagetoolplugin)
else()
    ecm_qt_declare_logging_category(languagetoolplugin_SRCS HEADER languagetoolplugin_debug.h IDENTIFIER KMAIL_EDITOR_LANGUAGETOOL_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_languagetoolplugin
        DESCRIPTION "kdepim-addons (languagetool plugin)"
        EXPORT KDEPIMADDONS
        )
endif()


kcoreaddons_add_plugin(kmail_languagetoolplugin JSON kmail_languagetoolplugin.json SOURCES
    ${languagetoolplugin_SRCS} INSTALL_NAMESPACE kmail/plugineditorgrammar)

target_link_libraries(kmail_languagetoolplugin
        KF5::MessageComposer KF5::I18n KF5::PimCommon KF5::XmlGui kmaillanguagetool  grammarcommon
    )
