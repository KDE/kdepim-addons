# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_standardsheaderstyleplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/messageviewer/headerstyle)
target_sources(messageviewer_standardsheaderstyleplugin PRIVATE
   standardsheaderstyleplugin.cpp
   standardsheaderstyleinterface.cpp
   standardheaderstrategy.cpp
   standardsheaderstyleplugin.h
   standardsheaderstyleinterface.h
   standardheaderstrategy.h
)


target_link_libraries(messageviewer_standardsheaderstyleplugin
  KPim${KF_MAJOR_VERSION}::MessageViewer
  KF${KF_MAJOR_VERSION}::XmlGui
  KF${KF_MAJOR_VERSION}::I18n
  KPim${KF_MAJOR_VERSION}::GrantleeTheme
)
