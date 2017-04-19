set(operaimporter_SRCS
   operaaddressbook.cpp  
   operaimportdata.cpp  
   operasettings.cpp
)

ecm_qt_declare_logging_category(operaimporter_SRCS HEADER operaplugin_debug.h IDENTIFIER OPERAPLUGIN_LOG CATEGORY_NAME org.kde.pim.importwizard.operaplugin)
kcoreaddons_add_plugin(operaimporterplugin JSON operaimporter.json SOURCES
    ${operaimporter_SRCS} INSTALL_NAMESPACE importwizard)


target_link_libraries(operaimporterplugin
  KPim::ImportWizard
  KF5::XmlGui
  KF5::I18n
  KF5::Contacts
  KF5::MailImporterAkonadi
  KF5::MailTransport
  KF5::MailCommon
  KF5::IdentityManagement
)
