# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(sieveeditoremailinedit_gui)
ecm_qt_declare_logging_category(sieveeditoremailinedit_gui HEADER sieveeditoremaillineditplugin_debug.h IDENTIFIER
    EMAILLINEEDITPLUGIN_LOG CATEGORY_NAME org.kde.pim.sieveeditoremaillinedit
    DESCRIPTION "kdepim-addons (SieveEditor email line plugin)"
    EXPORT KDEPIMADDONS
)

target_sources(sieveeditoremailinedit_gui PRIVATE
   main.cpp
   emaillineeditwidget.cpp
   emaillineeditwidget.h
   ../emaillineedit.cpp
)

target_link_libraries(sieveeditoremailinedit_gui
        KF6::I18n KF6::ColorScheme KPim6::KSieveUi KPim6::AkonadiContactWidgets
)
