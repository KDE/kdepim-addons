set(nylasmailimporter_SRCS
   nylasmailsettings.cpp
   nylasmaildata.cpp
)

ecm_qt_declare_logging_category(nylasmailimporter_SRCS HEADER nylasmailplugin_debug.h IDENTIFIER NYLASMAILPLUGIN_LOG CATEGORY_NAME org.kde.pim.importwizard.nylasmailplugin)
kcoreaddons_add_plugin(nylasmailimporterplugin JSON nylasmailimporter.json SOURCES
    ${nylasmailimporter_SRCS} INSTALL_NAMESPACE importwizard)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(nylasmailimporterplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(nylasmailimporterplugin
  KPim::ImportWizard
  KF5::XmlGui
  KF5::I18n
  KF5::Contacts
  KF5::MailImporterAkonadi
  KF5::MailTransport
  KF5::IdentityManagement
  KF5::MailCommon
)

