set(thebatimporter_SRCS
   thebatimportdata.cpp  
)

kcoreaddons_add_plugin(thebatimporterplugin JSON thebatimporter.json SOURCES
    ${thebatimporter_SRCS} INSTALL_NAMESPACE importwizard)


target_link_libraries(thebatimporterplugin
  KPim::ImportWizard
  KF5::XmlGui
  KF5::I18n
  KF5::Contacts
  KF5::MailImporterAkonadi
  KF5::MailTransport
  KF5::IdentityManagement
  KF5::MailCommon
)
