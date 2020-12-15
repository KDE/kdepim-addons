set(kaddressbook_importexport_vcard_SRCS
    vcardimportexportplugin.cpp
    vcardimportexportplugininterface.cpp
    engine/vcardviewerdialog.cpp
    engine/vcardexportselectionwidget.cpp
    )


kcoreaddons_add_plugin(kaddressbook_importexportvcardplugin JSON kaddressbook_importexportvcardplugin.json SOURCES
    ${kaddressbook_importexport_vcard_SRCS} INSTALL_NAMESPACE kaddressbook/importexportplugin)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_importexportvcardplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kaddressbook_importexportvcardplugin
    KPim::AddressbookImportExport
    KF5::PimCommon
    KF5::I18n
    KF5::XmlGui
    KF5::Contacts
    KF5::JobWidgets
    KF5::AkonadiContact
    Gpgmepp
    QGpgme
    )

