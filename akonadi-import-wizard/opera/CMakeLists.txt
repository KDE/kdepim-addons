# SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(operaimporterplugin INSTALL_NAMESPACE importwizard)
target_sources(operaimporterplugin PRIVATE
   operaaddressbook.cpp  
   operaimportdata.cpp  
   operasettings.cpp
)

ecm_qt_declare_logging_category(operaimporterplugin HEADER operaplugin_debug.h IDENTIFIER OPERAPLUGIN_LOG CATEGORY_NAME org.kde.pim.importwizard.operaplugin)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(operaimporterplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(operaimporterplugin
  KPim::ImportWizard
  KF5::XmlGui
  KF5::I18n
  KF5::Contacts
  KF5::MailImporterAkonadi
  KF5::MailTransport
  KF5::MailCommon
  KF5::IdentityManagement
)
