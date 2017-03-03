set(kmail_antivirusplugin_SRCS
    antivirusplugin.cpp
    antivirusplugininterface.cpp
    ../common/antispamwizard.cpp
)

kcoreaddons_add_plugin(kmail_antivirusplugin JSON kmail_antivirusplugin.json SOURCES
    ${kmail_antivirusplugin_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(kmail_antivirusplugin
  KF5::PimCommonAkonadi KF5::Completion KF5::IconThemes KF5::MailCommon KF5::XmlGui KF5::Libkdepim KF5::I18n
)
if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()
