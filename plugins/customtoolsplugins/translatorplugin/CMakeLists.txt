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
  KF5::XmlGui
  KF5::I18n
)

if (USE_KTEXTADDONS_LIB)
    target_link_libraries(pimcommon_translatorplugin KF5::TextTranslator)
else()
    target_link_libraries(pimcommon_translatorplugin KF5::PimCommonTextTranslator)
endif()
