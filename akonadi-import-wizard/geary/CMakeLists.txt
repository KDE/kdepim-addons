kcoreaddons_add_plugin(gearyimporterplugin JSON gearyimporter.json INSTALL_NAMESPACE importwizard)
target_sources(gearyimporterplugin PRIVATE
   gearyaddressbook.cpp  
   gearyimportdata.cpp  
   gearysettings.cpp
)

ecm_qt_declare_logging_category(gearyimporterplugin HEADER gearyplugin_debug.h IDENTIFIER GEARYPLUGIN_LOG CATEGORY_NAME org.kde.pim.importwizard.gearyplugin)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(gearyimporterplugin PROPERTIES UNITY_BUILD ON)
endif()


target_link_libraries(gearyimporterplugin
  KPim::ImportWizard
  KF5::XmlGui
  KF5::I18n
  KF5::Contacts
  KF5::MailImporterAkonadi
  KF5::MailTransport
  KF5::IdentityManagement
  KF5::MailCommon
)
