
set(kaddressbook_importexport_windowscontact_debugfile_SRCS)
ecm_qt_declare_logging_category(kaddressbook_importexport_windowscontact_debugfile_SRCS HEADER importexportwindowscontactplugin_debug.h IDENTIFIER IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG CATEGORY_NAME org.kde.pim.importexportwindowscontactplugin
    DESCRIPTION "kdepim-addons (Import/Export Windows Contact plugin)"
    EXPORT KDEPIMADDONS
    )
set(kaddressbook_importexport_windowscontact_SRCS
    ${kaddressbook_importexport_windowscontact_debugfile_SRCS}
    windowscontactimportexportplugin.cpp
    windowscontactimportexportplugininterface.cpp
    importwindowcontact.cpp
    )

kcoreaddons_add_plugin(kaddressbook_importexportwindowscontactplugin JSON kaddressbook_importexportwindowscontactplugin.json SOURCES
    ${kaddressbook_importexport_windowscontact_SRCS} INSTALL_NAMESPACE kaddressbook/importexportplugin)

target_link_libraries(kaddressbook_importexportwindowscontactplugin KF5::KaddressbookImportExport
        KF5::PimCommon
        KF5::I18n
        KF5::XmlGui
        KF5::Contacts
        KF5::JobWidgets
        KF5::Completion
        KF5::KIOWidgets
        KF5::AkonadiCore
        kaddressbookimportexportlibprivate
    )
if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
