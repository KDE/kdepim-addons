# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kaddressbook_importexportldapplugin INSTALL_NAMESPACE pim6/kaddressbook/importexportplugin)
target_sources(
    kaddressbook_importexportldapplugin
    PRIVATE
        ldapimportexportplugin.cpp
        ldapimportexportplugininterface.cpp
        ldapimportexportplugin.h
        ldapimportexportplugininterface.h
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        kaddressbook_importexportldapplugin
        PROPERTIES UNITY_BUILD ON
    )
endif()

target_link_libraries(
    kaddressbook_importexportldapplugin
    KPim6::AddressbookImportExport
    KPim6::AkonadiCore
    KF6::I18n
    KF6::XmlGui
    KF6::Contacts
    KPim6::PimCommonAkonadi
)
