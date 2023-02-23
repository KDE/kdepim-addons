# SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(evolutionv1importerplugin SOURCES
    evolutionv1importdata.cpp evolutionv1importdata.h INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/importwizard)


target_link_libraries(evolutionv1importerplugin
  KPim::ImportWizard
  KF${KF_MAJOR_VERSION}::XmlGui
  KF${KF_MAJOR_VERSION}::I18n
  KF${KF_MAJOR_VERSION}::Contacts
  KPim${KF_MAJOR_VERSION}::MailImporterAkonadi
  KPim${KF_MAJOR_VERSION}::MailTransport
  KPim${KF_MAJOR_VERSION}::MailCommon
  KPim${KF_MAJOR_VERSION}::IdentityManagement
  KF5::MessageViewer
)
