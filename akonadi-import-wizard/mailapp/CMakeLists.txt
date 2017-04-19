set(mailappimporter_SRCS
   mailappimportdata.cpp  
)

kcoreaddons_add_plugin(mailappimporterplugin JSON mailappimporter.json SOURCES
    ${mailappimporter_SRCS} INSTALL_NAMESPACE importwizard)


target_link_libraries(mailappimporterplugin
  KPim::ImportWizard
  KF5::XmlGui
  KF5::I18n
  KF5::Contacts
  KF5::MailImporterAkonadi
  KF5::MailTransport
  KF5::IdentityManagement
  KF5::MailCommon
)
