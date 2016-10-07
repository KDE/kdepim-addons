set(kaddressbook_importexport_gmx_SRCS
    gmximportexportplugin.cpp
    gmximportexportplugininterface.cpp
    )


kcoreaddons_add_plugin(kaddressbook_importexportgmxplugin JSON kaddressbook_importexportgmxplugin.json SOURCES
    ${kaddressbook_importexport_gmx_SRCS} INSTALL_NAMESPACE kaddressbook)

target_link_libraries(kaddressbook_importexportgmxplugin KF5::KaddressbookImportExport
        KF5::PimCommon
        KF5::I18n
        KF5::XmlGui
        KF5::Contacts
    )
