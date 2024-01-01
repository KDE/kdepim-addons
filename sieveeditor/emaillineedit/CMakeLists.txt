# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
include_directories(${CMAKE_CURRENT_BINARY_DIR})
kcoreaddons_add_plugin(emaillineeditplugin INSTALL_NAMESPACE pim6/libksieve)

ecm_qt_declare_logging_category(emaillineeditplugin HEADER sieveeditoremaillineditplugin_debug.h IDENTIFIER
    EMAILLINEEDITPLUGIN_LOG CATEGORY_NAME org.kde.pim.sieveeditoremaillinedit
    DESCRIPTION "kdepim-addons (SieveEditor email line plugin)"
    EXPORT KDEPIMADDONS
    )


if(BUILD_TESTING)
    add_subdirectory(tests)
    add_subdirectory(autotests)
endif()

target_sources(emaillineeditplugin PRIVATE
    emaillineedit.cpp
    emaillineedit.h
    )


target_link_libraries(emaillineeditplugin
        KF6::I18n KPim6::KSieveUi KPim6::AkonadiContactWidgets
    )



