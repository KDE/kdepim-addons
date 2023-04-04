# SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

set(thebatimporter_SRCS
   thebatimportdata.cpp  
)

kcoreaddons_add_plugin(thebatimporterplugin SOURCES
    ${thebatimporter_SRCS} INSTALL_NAMESPACE importwizard)


target_link_libraries(thebatimporterplugin
  KPim::ImportWizard
  KF6::XmlGui
  KF6::I18n
  KF6::Contacts
  KPim6::MailImporterAkonadi
  KPim6::MailTransport
  KPim6::IdentityManagement
  KPim6::MailCommon
)
