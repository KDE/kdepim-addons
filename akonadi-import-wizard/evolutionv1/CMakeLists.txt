# SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(evolutionv1importerplugin SOURCES
    evolutionv1importdata.cpp evolutionv1importdata.h INSTALL_NAMESPACE pim6/importwizard
)

target_link_libraries(
    evolutionv1importerplugin
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
