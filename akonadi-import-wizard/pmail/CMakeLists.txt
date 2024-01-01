# SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set(pmailimporter_SRCS
   pmailimportdata.cpp  
   pmailsettings.cpp
)

kcoreaddons_add_plugin(pmailimporterplugin SOURCES
    ${pmailimporter_SRCS} INSTALL_NAMESPACE importwizard)


target_link_libraries(pmailimporterplugin
  KPim::ImportWizard
  KF6::XmlGui
  KF6::I18n
  KF6::Contacts
  KPim6::MailImporterAkonadi
  KPim6::MailTransport
  KPim6::MailCommon
  KPim6::IdentityManagementCore
)
