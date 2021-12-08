# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kaddressbook_importexportvcardplugin INSTALL_NAMESPACE kaddressbook/importexportplugin)

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
    KF5::I18n
    KF5::XmlGui
    KF5::Contacts
    KF5::JobWidgets
    KF5::AkonadiContact
    Gpgmepp
    QGpgme
    )

