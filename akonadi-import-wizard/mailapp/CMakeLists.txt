# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(mailappimporterplugin INSTALL_NAMESPACE importwizard)
target_sources(mailappimporterplugin PRIVATE
   mailappimportdata.cpp
)

target_link_libraries(mailappimporterplugin
  KPim::ImportWizard
  KF5::XmlGui
  KF5::I18n
  KF5::Contacts
  KF5::MailImporterAkonadi
  KF5::MailTransport
  KF5::IdentityManagement
  KF5::MailCommon
)
