# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(headerstylemenu_gui headerstylemenu_gui.cpp)
target_link_libraries(
    headerstylemenu_gui
    KPim6::MessageViewer
    KF6::XmlGui
    KPim6::GrantleeTheme
    KF6::I18n
)
