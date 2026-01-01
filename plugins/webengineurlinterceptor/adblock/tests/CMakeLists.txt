# SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_executable(adblockdialog_gui)
target_sources(adblockdialog_gui PRIVATE adblockdialog_gui.cpp)

target_link_libraries(adblockdialog_gui KF6::I18n Qt::Widgets adblockplugin)
