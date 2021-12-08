# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kaddressbook_importexportldapplugin INSTALL_NAMESPACE kaddressbook/importexportplugin)
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
        KF5::I18n
        KF5::XmlGui
        KF5::Contacts
        KF5::PimCommonAkonadi
    )
