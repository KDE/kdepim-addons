# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(mailappimporterplugin INSTALL_NAMESPACE importwizard)
target_sources(mailappimporterplugin PRIVATE
   mailappimportdata.cpp
)

target_link_libraries(mailappimporterplugin
  KPim::ImportWizard
  KF${KF_MAJOR_VERSION}::XmlGui
  KF${KF_MAJOR_VERSION}::I18n
  KF${KF_MAJOR_VERSION}::Contacts
  KPim${KF_MAJOR_VERSION}::MailImporterAkonadi
  KF5::MailTransport
  KPim${KF_MAJOR_VERSION}::IdentityManagement
  KPim${KF_MAJOR_VERSION}::MailCommon
)
