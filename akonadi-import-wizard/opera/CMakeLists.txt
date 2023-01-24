# SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(operaimporterplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/importwizard)
target_sources(operaimporterplugin PRIVATE
   operaaddressbook.cpp  
   operaimportdata.cpp  
   operasettings.cpp
   operaaddressbook.h
   operaimportdata.h
   operasettings.h
)

ecm_qt_declare_logging_category(operaimporterplugin HEADER operaplugin_debug.h IDENTIFIER OPERAPLUGIN_LOG CATEGORY_NAME org.kde.pim.importwizard.operaplugin)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(operaimporterplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(operaimporterplugin
  KPim::ImportWizard
  KF${KF_MAJOR_VERSION}::XmlGui
  KF${KF_MAJOR_VERSION}::I18n
  KF${KF_MAJOR_VERSION}::Contacts
  KF5::MailImporterAkonadi
  KF5::MailTransport
  KF5::MailCommon
  KF5::IdentityManagement
)
