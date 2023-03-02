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
        KPim${KF_MAJOR_VERSION}::AddressbookImportExport
        KF5::PimCommon
        KF${KF_MAJOR_VERSION}::I18n
        KF${KF_MAJOR_VERSION}::XmlGui
        KF${KF_MAJOR_VERSION}::Contacts
        KF${KF_MAJOR_VERSION}::JobWidgets
        KPim${KF_MAJOR_VERSION}::AkonadiCore
    )
