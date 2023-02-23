# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(sieveeditorimapfoldercompletion_gui)
target_sources(sieveeditorimapfoldercompletion_gui PRIVATE
   main.cpp
   selectimapwidgettest.cpp
)

target_link_libraries(sieveeditorimapfoldercompletion_gui
     KF5::PimCommon KF${KF_MAJOR_VERSION}::Completion KF${KF_MAJOR_VERSION}::I18n KPim${KF_MAJOR_VERSION}::KSieveUi
)

