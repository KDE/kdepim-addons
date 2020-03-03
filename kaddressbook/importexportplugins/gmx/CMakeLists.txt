set(kaddressbook_importexport_gmx_SRCS
    gmximportexportplugin.cpp
    gmximportexportplugininterface.cpp
    )

if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(kaddressbook_importexport_gmx_SRCS HEADER kaddressbook_importexport_gmx_debug.h IDENTIFIER KADDRESSBOOK_IMPORTEXPORT_GMX_LOG CATEGORY_NAME org.kde.pim.kaddressbook_importexportgmx)
else()
    ecm_qt_declare_logging_category(kaddressbook_importexport_gmx_SRCS HEADER kaddressbook_importexport_gmx_debug.h IDENTIFIER KADDRESSBOOK_IMPORTEXPORT_GMX_LOG CATEGORY_NAME org.kde.pim.kaddressbook_importexportgmx
        DESCRIPTION "kdepim-addons (KAddressbook import export gmx plugin)"
        EXPORT KDEPIMADDONS
    )
endif()


kcoreaddons_add_plugin(kaddressbook_importexportgmxplugin JSON kaddressbook_importexportgmxplugin.json SOURCES
    ${kaddressbook_importexport_gmx_SRCS} INSTALL_NAMESPACE kaddressbook/importexportplugin)

target_link_libraries(kaddressbook_importexportgmxplugin KF5::KaddressbookImportExport
        KF5::PimCommon
        KF5::I18n
        KF5::XmlGui
        KF5::Contacts
        KF5::JobWidgets
        KF5::AkonadiCore
        kaddressbookimportexportlibprivate
    )
