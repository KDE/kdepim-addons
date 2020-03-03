if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

set(grammalecteplugin_SRCS
    grammalecteplugin.cpp
    grammalecteinterface.cpp
    )

if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(grammalecteplugin_SRCS HEADER grammalecteplugin_debug.h IDENTIFIER KMAIL_EDITOR_GRAMMALECTE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_grammalecteplugin)
else()
    ecm_qt_declare_logging_category(grammalecteplugin_SRCS HEADER grammalecteplugin_debug.h IDENTIFIER KMAIL_EDITOR_GRAMMALECTE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_grammalecteplugin
        DESCRIPTION "kdepim-addons (grammalecte plugin)"
        EXPORT KDEPIMADDONS
    )
endif()

kcoreaddons_add_plugin(kmail_grammalecteplugin JSON kmail_grammalecteplugin.json SOURCES
    ${grammalecteplugin_SRCS} INSTALL_NAMESPACE kmail/plugineditorgrammar)

target_link_libraries(kmail_grammalecteplugin
        KF5::MessageComposer KF5::I18n KF5::PimCommon KF5::XmlGui kmailgrammalecte  grammarcommon
    )
