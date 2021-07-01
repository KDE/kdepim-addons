# SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(nylasmailimporterplugin INSTALL_NAMESPACE importwizard)
target_sources(nylasmailimporterplugin PRIVATE
   nylasmailsettings.cpp
   nylasmaildata.cpp
)

ecm_qt_declare_logging_category(nylasmailimporterplugin HEADER nylasmailplugin_debug.h IDENTIFIER NYLASMAILPLUGIN_LOG CATEGORY_NAME org.kde.pim.importwizard.nylasmailplugin)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(nylasmailimporterplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(nylasmailimporterplugin
  KPim::ImportWizard
  KF5::XmlGui
  KF5::I18n
  KF5::Contacts
  KF5::MailImporterAkonadi
  KF5::MailTransport
  KF5::IdentityManagement
  KF5::MailCommon
)

