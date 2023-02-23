# SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

set(oeimporter_SRCS
   oeimportdata.cpp  
)

kcoreaddons_add_plugin(oeimporterplugin SOURCES
    ${oeimporter_SRCS} INSTALL_NAMESPACE importwizard)


target_link_libraries(oeimporterplugin
  KPim::ImportWizard
  KF${KF_MAJOR_VERSION}::XmlGui
  KF${KF_MAJOR_VERSION}::I18n
  KF${KF_MAJOR_VERSION}::Contacts
  KPim${KF_MAJOR_VERSION}::MailImporterAkonadi
  KF5::MailTransport
  KPim${KF_MAJOR_VERSION}::IdentityManagement
  KPim${KF_MAJOR_VERSION}::MailCommon
)
