# SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(evolutionv2importerplugin SOURCES
    evolutionv2importdata.cpp  evolutionv2importdata.h INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/importwizard)


target_link_libraries(evolutionv2importerplugin
  KPim::ImportWizard
  KF5::XmlGui
  KF5::I18n
  KF5::Contacts
  KF5::MailImporterAkonadi
  KF5::MailTransport
  KF5::MailCommon
  KF5::IdentityManagement
  KF5::MessageViewer
)
