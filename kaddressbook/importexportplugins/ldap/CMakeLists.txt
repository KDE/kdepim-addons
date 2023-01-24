# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kaddressbook_importexportldapplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kaddressbook/importexportplugin)
target_sources(kaddressbook_importexportldapplugin PRIVATE
    ldapimportexportplugin.cpp
    ldapimportexportplugininterface.cpp
    ldapimportexportplugin.h
    ldapimportexportplugininterface.h
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_importexportldapplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kaddressbook_importexportldapplugin
        KPim::AddressbookImportExport
        KF5::AkonadiCore
        KF${KF_MAJOR_VERSION}::I18n
        KF${KF_MAJOR_VERSION}::XmlGui
        KF${KF_MAJOR_VERSION}::Contacts
        KF5::PimCommonAkonadi
    )
