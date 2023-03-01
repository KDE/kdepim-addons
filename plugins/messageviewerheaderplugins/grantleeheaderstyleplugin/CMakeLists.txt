# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_grantleeheaderstyleplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/messageviewer/headerstyle)
target_sources(messageviewer_grantleeheaderstyleplugin PRIVATE
   grantleeheaderstyleplugin.cpp
   grantleeheaderstyleinterface.cpp
   grantleeheaderstrategy.cpp
   grantleeheaderstyleplugin.h
   grantleeheaderstyleinterface.h
   grantleeheaderstrategy.h
)

target_link_libraries(messageviewer_grantleeheaderstyleplugin
  KPim${KF_MAJOR_VERSION}::MessageViewer
  KPim${KF_MAJOR_VERSION}::GrantleeTheme
  KF${KF_MAJOR_VERSION}::XmlGui
)
