set(kaddressbook_importexport_ldap_SRCS
    ldapimportexportplugin.cpp
    ldapimportexportplugininterface.cpp
    )


kcoreaddons_add_plugin(kaddressbook_importexportldapplugin JSON kaddressbook_importexportldapplugin.json SOURCES
    ${kaddressbook_importexport_ldap_SRCS} INSTALL_NAMESPACE kaddressbook/importexportplugin)
if (COMPILE_WITH_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_importexportldapplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kaddressbook_importexportldapplugin
        KPim::AddressbookImportExport
        KF5::AkonadiCore
        KF5::I18n
        KF5::XmlGui
        KF5::Contacts
        KF5::PimCommonAkonadi
    )
