set(kmail_antispamplugin_SRCS
    antispamplugin.cpp
    antispamplugininterface.cpp
    ../common/antispamwizard.cpp
)

add_library(kmail_antispamplugin MODULE ${kmail_antispamplugin_SRCS})

target_link_libraries(kmail_antispamplugin
  KF5::PimCommon KF5::Completion KF5::IconThemes KF5::MailCommon KF5::XmlGui KF5::Libkdepim KF5::I18n
)

install(TARGETS kmail_antispamplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kmail)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()
