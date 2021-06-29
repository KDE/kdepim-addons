if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

kcoreaddons_add_plugin(kmail_grammalecteplugin INSTALL_NAMESPACE kmail/plugineditorgrammar)
target_sources(kmail_grammalecteplugin PRIVATE
    grammalecteplugin.cpp
    grammalecteinterface.cpp
    )

ecm_qt_declare_logging_category(kmail_grammalecteplugin HEADER grammalecteplugin_debug.h IDENTIFIER KMAIL_EDITOR_GRAMMALECTE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_grammalecteplugin
    DESCRIPTION "kdepim-addons (grammalecte plugin)"
    EXPORT KDEPIMADDONS
    )


target_link_libraries(kmail_grammalecteplugin
    KF5::MessageComposer KF5::I18n KF5::PimCommon KF5::XmlGui kmailgrammalecte  grammarcommon
    )
