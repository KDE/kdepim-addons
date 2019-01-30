set(kmail_grammalecteplugin_SRCS
    grammalecteparser.cpp
    )

ecm_qt_declare_logging_category(kmail_grammalecteplugin_SRCS HEADER grammalecteplugin_debug.h IDENTIFIER KMAIL_EDITOR_GRAMMALECTE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_grammalecteplugin)

kcoreaddons_add_plugin(kmail_grammalecteplugin JSON kmail_grammalecteplugin.json SOURCES
    ${kmail_grammalecteplugin_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(kmail_grammalecteplugin
        KF5::IconThemes KF5::MessageComposer KF5::I18n KF5::PimCommon
    )
