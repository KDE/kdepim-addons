set(kmail_antivirusplugin_SRCS
    antivirusplugin.cpp
    antivirusplugininterface.cpp
    ../common/antispamwizard.cpp
    ../common/antispam.qrc
)

kcoreaddons_add_plugin(kmail_antivirusplugin JSON kmail_antivirusplugin.json SOURCES
    ${kmail_antivirusplugin_SRCS} INSTALL_NAMESPACE kmail/mainview)

target_link_libraries(kmail_antivirusplugin
  KF5::PimCommonAkonadi KF5::Completion KF5::MailCommon KF5::AkonadiWidgets KF5::XmlGui KF5::Libkdepim KF5::I18n KF5::GuiAddons
)
if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()
