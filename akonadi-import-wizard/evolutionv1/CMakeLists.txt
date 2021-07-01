# SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(evolutionv1importerplugin SOURCES
    evolutionv1importdata.cpp INSTALL_NAMESPACE importwizard)


target_link_libraries(evolutionv1importerplugin
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
