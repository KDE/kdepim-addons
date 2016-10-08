set(kaddressbook_importexport_ldap_SRCS
    ldapimportexportplugin.cpp
    ldapimportexportplugininterface.cpp
    )


kcoreaddons_add_plugin(kaddressbook_importexportldapplugin JSON kaddressbook_importexportldapplugin.json SOURCES
    ${kaddressbook_importexport_ldap_SRCS} INSTALL_NAMESPACE kaddressbook)

target_link_libraries(kaddressbook_importexportldapplugin KF5::KaddressbookImportExport
        KF5::PimCommon
        KF5::I18n
        KF5::XmlGui
        KF5::Contacts
    )
