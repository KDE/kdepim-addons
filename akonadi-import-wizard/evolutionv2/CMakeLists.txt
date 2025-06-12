# SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(evolutionv2importerplugin SOURCES
    evolutionv2importdata.cpp  evolutionv2importdata.h INSTALL_NAMESPACE pim6/importwizard
)

target_link_libraries(
    evolutionv2importerplugin
    KPim6::ImportWizard
    KF6::XmlGui
    KF6::I18n
    KF6::Contacts
    KPim6::MailImporterAkonadi
    KPim6::MailTransport
    KPim6::MailCommon
    KPim6::IdentityManagementCore
    KPim6::MessageViewer
)
