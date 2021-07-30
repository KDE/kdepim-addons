# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_longheaderstyleplugin INSTALL_NAMESPACE messageviewer/headerstyle)
target_sources(messageviewer_longheaderstyleplugin PRIVATE
   longheaderstyleplugin.cpp
   longheaderstyleinterface.cpp
)


target_link_libraries(messageviewer_longheaderstyleplugin
  KF5::MessageViewer
  KF5::XmlGui
  KF5::I18n
)
