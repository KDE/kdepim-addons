set(kmail_expertplugin_SRCS
    expertplugin.cpp
    expertplugininterface.cpp
)

if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(kmail_expertplugin_SRCS
        HEADER expertplugin_debug.h
        IDENTIFIER KMAIL_EXPERT_PLUGIN_LOG
        CATEGORY_NAME org.kde.pim.kmail_expertplugin)
else()
    ecm_qt_declare_logging_category(kmail_expertplugin_SRCS
        HEADER expertplugin_debug.h
        IDENTIFIER KMAIL_EXPERT_PLUGIN_LOG
        CATEGORY_NAME org.kde.pim.kmail_expertplugin
        DESCRIPTION "kdepim-addons (kmail expert plugin)"
        EXPORT KDEPIMADDONS
        )
endif()

kcoreaddons_add_plugin(kmail_expertplugin JSON kmail_expertplugin.json SOURCES
    ${kmail_expertplugin_SRCS} INSTALL_NAMESPACE kmail/mainview)

target_link_libraries(kmail_expertplugin
  KF5::PimCommon KF5::PimCommonAkonadi KF5::XmlGui KF5::Libkdepim KF5::I18n
)
if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()
