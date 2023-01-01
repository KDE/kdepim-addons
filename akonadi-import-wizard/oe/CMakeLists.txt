# SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

set(oeimporter_SRCS
   oeimportdata.cpp  
)

kcoreaddons_add_plugin(oeimporterplugin SOURCES
    ${oeimporter_SRCS} INSTALL_NAMESPACE importwizard)


target_link_libraries(oeimporterplugin
  KPim::ImportWizard
  KF5::XmlGui
  KF5::I18n
  KF5::Contacts
  KF5::MailImporterAkonadi
  KF5::MailTransport
  KF5::IdentityManagement
  KF5::MailCommon
)
