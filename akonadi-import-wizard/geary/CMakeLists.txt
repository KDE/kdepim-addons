# SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(gearyimporterplugin INSTALL_NAMESPACE pim6/importwizard)
target_sources(
    gearyimporterplugin
    PRIVATE
        gearyaddressbook.cpp
        gearyimportdata.cpp
        gearysettings.cpp
        gearyaddressbook.h
        gearyimportdata.h
        gearysettings.h
)

ecm_qt_declare_logging_category(gearyimporterplugin HEADER gearyplugin_debug.h IDENTIFIER GEARYPLUGIN_LOG CATEGORY_NAME org.kde.pim.importwizard.gearyplugin)
if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(gearyimporterplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(
    gearyimporterplugin
    KPim6::ImportWizard
    KF6::XmlGui
    KF6::I18n
    KF6::Contacts
    KPim6::MailImporterAkonadi
    KPim6::MailTransport
    KPim6::IdentityManagementCore
    KPim6::MailCommon
)
