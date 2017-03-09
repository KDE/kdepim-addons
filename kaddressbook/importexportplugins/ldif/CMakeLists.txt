set(kaddressbook_importexport_ldif_SRCS
    ldifimportexportplugin.cpp
    ldifimportexportplugininterface.cpp
    )


kcoreaddons_add_plugin(kaddressbook_importexportldifplugin JSON kaddressbook_importexportldifplugin.json SOURCES
    ${kaddressbook_importexport_ldif_SRCS} INSTALL_NAMESPACE kaddressbook)

target_link_libraries(kaddressbook_importexportldifplugin KF5::KaddressbookImportExport
        KF5::PimCommon
        KF5::I18n
        KF5::XmlGui
        KF5::Contacts
        KF5::JobWidgets
        KF5::AkonadiCore
        kaddressbookimportexportlibprivate
    )
