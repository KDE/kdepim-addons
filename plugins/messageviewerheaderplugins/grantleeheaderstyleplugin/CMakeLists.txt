# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_grantleeheaderstyleplugin INSTALL_NAMESPACE pim6/messageviewer/headerstyle)
target_sources(messageviewer_grantleeheaderstyleplugin PRIVATE
   grantleeheaderstyleplugin.cpp
   grantleeheaderstyleinterface.cpp
   grantleeheaderstrategy.cpp
   grantleeheaderstyleplugin.h
   grantleeheaderstyleinterface.h
   grantleeheaderstrategy.h
)

target_link_libraries(messageviewer_grantleeheaderstyleplugin
  KPim6::MessageViewer
  KPim6::GrantleeTheme
  KF6::XmlGui
)
