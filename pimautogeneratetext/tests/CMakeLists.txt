# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

add_executable(
    autogenerateconfigureaskdialog_gui
    autogenerateconfigureaskdialog_gui.cpp
)

target_link_libraries(
    autogenerateconfigureaskdialog_gui
    KPim6::AutoGenerateText
)
