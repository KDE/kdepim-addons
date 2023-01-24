# SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

set(thebatimporter_SRCS
   thebatimportdata.cpp  
)

kcoreaddons_add_plugin(thebatimporterplugin SOURCES
    ${thebatimporter_SRCS} INSTALL_NAMESPACE importwizard)


target_link_libraries(thebatimporterplugin
  KPim::ImportWizard
  KF${KF_MAJOR_VERSION}::XmlGui
  KF${KF_MAJOR_VERSION}::I18n
  KF${KF_MAJOR_VERSION}::Contacts
  KF5::MailImporterAkonadi
  KF5::MailTransport
  KF5::IdentityManagement
  KF5::MailCommon
)
