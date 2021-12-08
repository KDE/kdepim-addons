# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kaddressbook_importexportldifplugin INSTALL_NAMESPACE kaddressbook/importexportplugin)
target_sources(kaddressbook_importexportldifplugin PRIVATE
    ldifimportexportplugin.cpp
    ldifimportexportplugininterface.cpp
    ldifimportexportplugin.h
    ldifimportexportplugininterface.h
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_importexportldifplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kaddressbook_importexportldifplugin
        KPim::AddressbookImportExport
        KF5::PimCommon
        KF5::I18n
        KF5::XmlGui
        KF5::Contacts
        KF5::JobWidgets
        KF5::AkonadiCore
    )
