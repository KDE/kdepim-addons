set(kmail_antispamplugin_SRCS
    antispamplugin.cpp
    antispamplugininterface.cpp
    ../common/antispamwizard.cpp
)

kcoreaddons_add_plugin(kmail_antispamplugin JSON kmail_antispamplugin.json SOURCES
    ${kmail_antispamplugin_SRCS} INSTALL_NAMESPACE kmail)
target_link_libraries(kmail_antispamplugin
  KF5::PimCommon KF5::Completion KF5::IconThemes KF5::MailCommon KF5::XmlGui KF5::Libkdepim KF5::I18n
)


if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()
