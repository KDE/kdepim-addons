# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_gravatarconfigplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/messageviewer/configuresettings)
target_sources(messageviewer_gravatarconfigplugin PRIVATE
   gravatarconfiguresettingspluginwidget.cpp
   gravatarconfiguresettingsplugin.cpp
   gravatarconfiguresettingsplugindialog.cpp
   gravatarconfiguresettingspluginwidget.h
   gravatarconfiguresettingsplugin.h
   gravatarconfiguresettingsplugindialog.h
)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_gravatarconfigplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_gravatarconfigplugin
  KPim6::MessageViewer
  KPim6::PimCommon
  KPim6::Gravatar
  KF6::I18n
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

