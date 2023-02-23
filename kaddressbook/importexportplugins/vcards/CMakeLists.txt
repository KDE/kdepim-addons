# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kaddressbook_importexportvcardplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kaddressbook/importexportplugin)

target_sources(kaddressbook_importexportvcardplugin PRIVATE
    vcardimportexportplugin.cpp
    vcardimportexportplugininterface.cpp
    engine/vcardviewerdialog.cpp
    engine/vcardexportselectionwidget.cpp
    vcardimportexportplugin.h
    vcardimportexportplugininterface.h
    engine/vcardviewerdialog.h
    engine/vcardexportselectionwidget.h
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_importexportvcardplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kaddressbook_importexportvcardplugin
    KPim::AddressbookImportExport
    KF5::PimCommon
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::XmlGui
    KF${KF_MAJOR_VERSION}::Contacts
    KF${KF_MAJOR_VERSION}::JobWidgets
    KPim${KF_MAJOR_VERSION}::AkonadiContact
    Gpgmepp
    )
if (QT_MAJOR_VERSION STREQUAL "6")
    target_link_libraries(kaddressbook_importexportvcardplugin QGpgmeQt6)
else()
    target_link_libraries(kaddressbook_importexportvcardplugin QGpgme)
endif()
