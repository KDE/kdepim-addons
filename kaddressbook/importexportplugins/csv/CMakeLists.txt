set(kaddressbook_importexport_csv_SRCS
    csvimportexportplugin.cpp
    csvimportexportplugininterface.cpp
    )


kcoreaddons_add_plugin(kaddressbook_importexportcsvplugin JSON kaddressbook_importexportcsvplugin.json SOURCES
    ${kaddressbook_importexport_csv_SRCS} INSTALL_NAMESPACE kaddressbook)

target_link_libraries(kaddressbook_importexportcsvplugin KF5::KaddressbookImportExport
        KF5::PimCommon
        KF5::I18n
        KF5::XmlGui
        KF5::Contacts
    )
