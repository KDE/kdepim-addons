# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kaddressbook_importexportgmxplugin INSTALL_NAMESPACE kaddressbook/importexportplugin)
target_sources(kaddressbook_importexportgmxplugin PRIVATE
    gmximportexportplugin.cpp
    gmximportexportplugininterface.cpp
    gmximportexportplugin.h
    gmximportexportplugininterface.h
    )

ecm_qt_declare_logging_category(kaddressbook_importexportgmxplugin HEADER kaddressbook_importexport_gmx_debug.h IDENTIFIER KADDRESSBOOK_IMPORTEXPORT_GMX_LOG CATEGORY_NAME org.kde.pim.kaddressbook_importexportgmx
    DESCRIPTION "kdepim-addons (KAddressbook import export gmx plugin)"
    EXPORT KDEPIMADDONS
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
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
