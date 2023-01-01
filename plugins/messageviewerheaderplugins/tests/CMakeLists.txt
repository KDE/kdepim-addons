# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(headerstylemenu_gui headerstylemenu_gui.cpp)
target_link_libraries(headerstylemenu_gui
  KF5::MessageViewer
  KF5::XmlGui
  KF5::GrantleeTheme
  KF5::I18n
)

