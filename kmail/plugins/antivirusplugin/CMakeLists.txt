set(kmail_antivirusplugin_SRCS
    antivirusplugin.cpp
    antivirusplugininterface.cpp
    ../common/antispamwizard.cpp
)

add_library(kmail_antivirusplugin MODULE ${kmail_antivirusplugin_SRCS})

target_link_libraries(kmail_antivirusplugin
  KF5::PimCommon KF5::Completion KF5::IconThemes KF5::MailCommon KF5::XmlGui
)

install(TARGETS kmail_antivirusplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kmail)
kcoreaddons_desktop_to_json(kmail_antivirusplugin kmail_antivirusplugin.desktop)

