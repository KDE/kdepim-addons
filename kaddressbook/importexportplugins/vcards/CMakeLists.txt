set(kaddressbook_importexport_vcard_SRCS
    vcardimportexportplugin.cpp
    vcardimportexportplugininterface.cpp
    engine/vcardviewerdialog.cpp
    engine/vcardexportselectionwidget.cpp
    )


kcoreaddons_add_plugin(kaddressbook_importexportvcardplugin JSON kaddressbook_importexportvcardplugin.json SOURCES
    ${kaddressbook_importexport_vcard_SRCS} INSTALL_NAMESPACE kaddressbook)

target_link_libraries(kaddressbook_importexportvcardplugin
    KF5::KaddressbookImportExport
        KF5::PimCommon
        KF5::I18n
        KF5::XmlGui
        KF5::Contacts
        KF5::KaddressbookGrantlee
        KF5::JobWidgets
        kaddressbookimportexportlibprivate
    )
if (WIN32)
    target_link_libraries(kaddressbook_importexportvcardplugin KF5::Gpgmepp)
else()
    target_link_libraries(kaddressbook_importexportvcardplugin KF5::Gpgmepp-pthread)
endif()
if(KF5Gpgmepp_FOUND)
    target_link_libraries(kaddressbook_importexportvcardplugin KF5::QGpgme)
endif()

