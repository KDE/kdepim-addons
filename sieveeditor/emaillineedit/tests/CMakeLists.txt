# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
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
   ../emaillineedit.cpp
)

target_link_libraries(sieveeditoremailinedit_gui
     KF5::I18n KF5::KSieveUi KF5::AkonadiContact
)
