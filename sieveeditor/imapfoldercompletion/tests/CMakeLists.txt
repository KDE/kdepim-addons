# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(sieveeditorimapfoldercompletion_gui)
target_sources(
    sieveeditorimapfoldercompletion_gui
    PRIVATE main.cpp selectimapwidgettest.cpp
)

target_link_libraries(
    sieveeditorimapfoldercompletion_gui
    KPim6::PimCommon
    KF6::Completion
    KF6::I18n
    KPim6::KSieveUi
)
