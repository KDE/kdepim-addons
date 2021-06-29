kcoreaddons_add_plugin(kaddressbook_importexportcsvplugin INSTALL_NAMESPACE kaddressbook/importexportplugin)
target_sources(kaddressbook_importexportcsvplugin PRIVATE
    csvimportexportplugin.cpp
    csvimportexportplugininterface.cpp
    import/csvimportdialog.cpp
    import/dateparser.cpp
    import/qcsvmodel.cpp
    import/qcsvreader.cpp
    import/templateselectiondialog.cpp
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_importexportcsvplugin PROPERTIES UNITY_BUILD ON)
endif()
target_link_libraries(kaddressbook_importexportcsvplugin
        KPim::AddressbookImportExport
        KF5::PimCommon
        KF5::I18n
        KF5::XmlGui
        KF5::Contacts
        KF5::JobWidgets
        KF5::Completion
        KF5::KIOWidgets
        KF5::AkonadiCore
    )
