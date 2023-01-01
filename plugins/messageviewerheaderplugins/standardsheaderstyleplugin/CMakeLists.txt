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
  KF5::MessageViewer
  KF5::XmlGui
  KF5::I18n
  KF5::GrantleeTheme
)
