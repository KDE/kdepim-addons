# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_longheaderstyleplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/messageviewer/headerstyle)
target_sources(messageviewer_longheaderstyleplugin PRIVATE
   longheaderstyleplugin.cpp
   longheaderstyleinterface.cpp
   longheaderstyleplugin.h
   longheaderstyleinterface.h
)


target_link_libraries(messageviewer_longheaderstyleplugin
  KPim6::MessageViewer
  KF6::XmlGui
  KF6::I18n
)
