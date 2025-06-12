# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(mailappimporterplugin INSTALL_NAMESPACE importwizard)
target_sources(mailappimporterplugin PRIVATE mailappimportdata.cpp)

target_link_libraries(
    mailappimporterplugin
    KPim6::ImportWizard
    KF6::XmlGui
    KF6::I18n
    KF6::Contacts
    KPim6::MailImporterAkonadi
    KPim6::MailTransport
    KPim6::IdentityManagementCore
    KPim6::MailCommon
)
