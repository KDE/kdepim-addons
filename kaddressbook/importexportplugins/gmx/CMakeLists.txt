set(kaddressbook_importexport_gmx_SRCS
    gmximportexportplugin.cpp
    gmximportexportplugininterface.cpp
    )

ecm_qt_declare_logging_category(kaddressbook_importexport_gmx_SRCS HEADER kaddressbook_importexport_gmx_debug.h IDENTIFIER KADDRESSBOOK_IMPORTEXPORT_GMX_LOG CATEGORY_NAME org.kde.pim.kaddressbook_importexportgmx
    DESCRIPTION "kdepim-addons (KAddressbook import export gmx plugin)"
    EXPORT KDEPIMADDONS
    )


kcoreaddons_add_plugin(kaddressbook_importexportgmxplugin JSON kaddressbook_importexportgmxplugin.json SOURCES
    ${kaddressbook_importexport_gmx_SRCS} INSTALL_NAMESPACE kaddressbook/importexportplugin)
if (COMPILE_WITH_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_importexportgmxplugin PROPERTIES UNITY_BUILD ON)
endif()
target_link_libraries(kaddressbook_importexportgmxplugin
    KPim::AddressbookImportExport
    KF5::PimCommon
    KF5::I18n
    KF5::XmlGui
    KF5::Contacts
    KF5::JobWidgets
    KF5::AkonadiCore
    )
