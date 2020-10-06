set(kmail_antispamplugin_SRCS
    antispamplugin.cpp
    antispamplugininterface.cpp
    ../common/antispamwizard.cpp
    ../common/antispam.qrc
)

kcoreaddons_add_plugin(kmail_antispamplugin JSON kmail_antispamplugin.json SOURCES
    ${kmail_antispamplugin_SRCS} INSTALL_NAMESPACE kmail/mainview)
target_link_libraries(kmail_antispamplugin
  KF5::PimCommonAkonadi KF5::Completion KF5::MailCommon KF5::XmlGui KF5::I18n KF5::GuiAddons
)


if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()
