# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_fancyheaderstyleplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/messageviewer/headerstyle)
target_sources(messageviewer_fancyheaderstyleplugin PRIVATE
   fancyheaderstyleplugin.cpp
   fancyheaderstyleinterface.cpp
   fancyheaderstyle.cpp
   fancyheaderstyleplugin.h
   fancyheaderstyleinterface.h
   fancyheaderstyle.h
)


target_link_libraries(messageviewer_fancyheaderstyleplugin
  KF5::MessageViewer
  KF${KF_MAJOR_VERSION}::XmlGui
  KF${KF_MAJOR_VERSION}::I18n
)
