set(pmailimporter_SRCS
   pmailimportdata.cpp  
   pmailsettings.cpp
)

kcoreaddons_add_plugin(pmailimporterplugin SOURCES
    ${pmailimporter_SRCS} INSTALL_NAMESPACE importwizard)


target_link_libraries(pmailimporterplugin
  KPim::ImportWizard
  KF5::XmlGui
  KF5::I18n
  KF5::Contacts
  KF5::MailImporterAkonadi
  KF5::MailTransport
  KF5::MailCommon
  KF5::IdentityManagement
)
