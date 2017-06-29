set(mailtransport_sendplugin_SRCS
   sendmailtransportplugin.cpp
   sendmailjob.cpp
)

kcoreaddons_add_plugin(mailtransport_sendplugin JSON sendmailtransport.json SOURCES
    ${mailtransport_sendplugin_SRCS} INSTALL_NAMESPACE mailtransport)

target_link_libraries(mailtransport_sendplugin
  KF5::MailTransport KF5::CoreAddons KF5::I18n KF5::ConfigWidgets
)
