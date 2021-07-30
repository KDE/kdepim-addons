# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_fancyheaderstyleplugin INSTALL_NAMESPACE messageviewer/headerstyle)
target_sources(messageviewer_fancyheaderstyleplugin PRIVATE
   fancyheaderstyleplugin.cpp
   fancyheaderstyleinterface.cpp
   fancyheaderstyle.cpp
)


target_link_libraries(messageviewer_fancyheaderstyleplugin
  KF5::MessageViewer
  KF5::XmlGui
  KF5::I18n
)
