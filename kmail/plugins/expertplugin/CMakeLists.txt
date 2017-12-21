set(kmail_expertplugin_SRCS
    expertplugin.cpp
    expertplugininterface.cpp
)

ecm_qt_declare_logging_category(kmail_expertplugin_SRCS
    HEADER expertplugin_debug.h
    IDENTIFIER KMAIL_EXPERT_PLUGIN_LOG
    CATEGORY_NAME org.kde.pim.kmail_expertplugin)

kcoreaddons_add_plugin(kmail_expertplugin JSON kmail_expertplugin.json SOURCES
    ${kmail_expertplugin_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(kmail_expertplugin
  KF5::PimCommon KF5::IconThemes KF5::PimCommonAkonadi KF5::XmlGui KF5::Libkdepim KF5::I18n
)
if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()
