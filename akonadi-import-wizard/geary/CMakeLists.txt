# SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(gearyimporterplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/importwizard)
target_sources(gearyimporterplugin PRIVATE
   gearyaddressbook.cpp  
   gearyimportdata.cpp  
   gearysettings.cpp
   gearyaddressbook.h
   gearyimportdata.h
   gearysettings.h
)

ecm_qt_declare_logging_category(gearyimporterplugin HEADER gearyplugin_debug.h IDENTIFIER GEARYPLUGIN_LOG CATEGORY_NAME org.kde.pim.importwizard.gearyplugin)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(gearyimporterplugin PROPERTIES UNITY_BUILD ON)
endif()


target_link_libraries(gearyimporterplugin
  KPim::ImportWizard
  KF${KF_MAJOR_VERSION}::XmlGui
  KF${KF_MAJOR_VERSION}::I18n
  KF${KF_MAJOR_VERSION}::Contacts
  KF5::MailImporterAkonadi
  KF5::MailTransport
  KPim${KF_MAJOR_VERSION}::IdentityManagement
  KF5::MailCommon
)
