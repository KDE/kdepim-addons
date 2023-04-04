# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kaddressbook_importexportwindowscontactplugin INSTALL_NAMESPACE pim6/kaddressbook/importexportplugin)

ecm_qt_declare_logging_category(kaddressbook_importexportwindowscontactplugin HEADER importexportwindowscontactplugin_debug.h IDENTIFIER IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG CATEGORY_NAME org.kde.pim.importexportwindowscontactplugin
    DESCRIPTION "kdepim-addons (Import/Export Windows Contact plugin)"
    EXPORT KDEPIMADDONS
    )
target_sources(kaddressbook_importexportwindowscontactplugin PRIVATE
    ${kaddressbook_importexport_windowscontact_debugfile_SRCS}
    windowscontactimportexportplugin.cpp
    windowscontactimportexportplugininterface.cpp
    importwindowcontact.cpp
    windowscontactimportexportplugin.h
    windowscontactimportexportplugininterface.h
    importwindowcontact.h
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_importexportwindowscontactplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kaddressbook_importexportwindowscontactplugin
    KPim6::AddressbookImportExport
    KPim6::PimCommon
    KF6::I18n
    KF6::XmlGui
    KF6::Contacts
    KF6::JobWidgets
    KF6::Completion
    KF6::KIOWidgets
    KPim6::AkonadiCore
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
