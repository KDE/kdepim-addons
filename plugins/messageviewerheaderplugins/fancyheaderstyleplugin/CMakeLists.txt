# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_fancyheaderstyleplugin INSTALL_NAMESPACE pim6/messageviewer/headerstyle)
target_sources(messageviewer_fancyheaderstyleplugin PRIVATE
   fancyheaderstyleplugin.cpp
   fancyheaderstyleinterface.cpp
   fancyheaderstyle.cpp
   fancyheaderstyleplugin.h
   fancyheaderstyleinterface.h
   fancyheaderstyle.h
)


target_link_libraries(messageviewer_fancyheaderstyleplugin
  KPim6::MessageViewer
  KF6::XmlGui
  KF6::I18n
)
