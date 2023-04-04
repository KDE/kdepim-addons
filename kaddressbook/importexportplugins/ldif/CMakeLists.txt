# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kaddressbook_importexportldifplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kaddressbook/importexportplugin)
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
        KPim6::AddressbookImportExport
        KPim6::PimCommon
        KF6::I18n
        KF6::XmlGui
        KF6::Contacts
        KF6::JobWidgets
        KPim6::AkonadiCore
    )
