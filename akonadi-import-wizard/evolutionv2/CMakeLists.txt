kcoreaddons_add_plugin(evolutionv2importerplugin JSON evolutionv2importer.json SOURCES
    evolutionv2importdata.cpp   INSTALL_NAMESPACE importwizard)


target_link_libraries(evolutionv2importerplugin
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
