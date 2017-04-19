set(evolutionv1importer_SRCS
   evolutionv1importdata.cpp  
)

kcoreaddons_add_plugin(evolutionv1importerplugin JSON evolutionv1importer.json SOURCES
    ${evolutionv1importer_SRCS} INSTALL_NAMESPACE importwizard)


target_link_libraries(evolutionv1importerplugin
  KPim::ImportWizard
  KF5::XmlGui
  KF5::I18n
  KF5::Contacts
  KF5::MailImporterAkonadi
  KF5::MailTransport
  KF5::MailCommon
  KF5::IdentityManagement
  KF5::MessageViewer
)
