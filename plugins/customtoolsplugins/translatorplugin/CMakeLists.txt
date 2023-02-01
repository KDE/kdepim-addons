# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(pimcommon_translatorplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/pimcommon/customtools)
target_sources(pimcommon_translatorplugin PRIVATE
   translatorplugin.cpp
   translatorview.cpp
   translatorplugin.h
   translatorview.h
)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(pimcommon_translatorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(pimcommon_translatorplugin
  KF5::PimCommon
  KF5::PimTextEdit
  KF${KF_MAJOR_VERSION}::XmlGui
  KF${KF_MAJOR_VERSION}::I18n
  KF${KF_MAJOR_VERSION}::TextTranslator
)

