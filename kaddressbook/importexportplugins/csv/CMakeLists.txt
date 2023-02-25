# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kaddressbook_importexportcsvplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kaddressbook/importexportplugin)
target_sources(kaddressbook_importexportcsvplugin PRIVATE
    csvimportexportplugin.cpp
    csvimportexportplugininterface.cpp
    import/csvimportdialog.cpp
    import/dateparser.cpp
    import/qcsvmodel.cpp
    import/qcsvreader.cpp
    import/templateselectiondialog.cpp
    csvimportexportplugin.h
    csvimportexportplugininterface.h
    import/csvimportdialog.h
    import/dateparser.h
    import/qcsvmodel.h
    import/qcsvreader.h
    import/templateselectiondialog.h
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_importexportcsvplugin PROPERTIES UNITY_BUILD ON)
endif()
target_link_libraries(kaddressbook_importexportcsvplugin
        KPim${KF_MAJOR_VERSION}::AddressbookImportExport
        KF5::PimCommon
        KF${KF_MAJOR_VERSION}::I18n
        KF${KF_MAJOR_VERSION}::XmlGui
        KF${KF_MAJOR_VERSION}::Contacts
        KF${KF_MAJOR_VERSION}::JobWidgets
        KF${KF_MAJOR_VERSION}::Completion
        KF${KF_MAJOR_VERSION}::KIOWidgets
        KF5::AkonadiCore
    )
