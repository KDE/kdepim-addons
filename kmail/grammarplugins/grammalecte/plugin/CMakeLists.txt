if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

set(grammalecteplugin_SRCS
    grammalecteplugin.cpp
    grammalecteinterface.cpp
    )

ecm_qt_declare_logging_category(grammalecteplugin_SRCS HEADER grammalecteplugin_debug.h IDENTIFIER KMAIL_EDITOR_GRAMMALECTE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_grammalecteplugin)

kcoreaddons_add_plugin(kmail_grammalecteplugin JSON kmail_grammalecteplugin.json SOURCES
    ${grammalecteplugin_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(kmail_grammalecteplugin
        KF5::IconThemes KF5::MessageComposer KF5::I18n KF5::PimCommon KF5::XmlGui kmailgrammalecte
    )
