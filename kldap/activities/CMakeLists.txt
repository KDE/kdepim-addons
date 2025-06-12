# SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

include_directories(${CMAKE_CURRENT_BINARY_DIR})
kcoreaddons_add_plugin(kldapactivitiesplugin INSTALL_NAMESPACE "pim6/ldapactivities")

ecm_qt_declare_logging_category(kldapactivitiesplugin HEADER kldapactivitiesplugin_debug.h IDENTIFIER
    KMAILTRANSPORTACTIVITIES_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kldapactivitiesplugin
    DESCRIPTION "kdepim-addons (KLDap activities support)"
    EXPORT KDEPIMADDONS
)

target_sources(
    kldapactivitiesplugin
    PRIVATE ldapactivitiesplugin.h ldapactivitiesplugin.cpp
)

target_link_libraries(
    kldapactivitiesplugin
    KF6::I18n
    KF6::CoreAddons
    Qt::Widgets
    KPim6::PimCommonActivities
    KPim6::LdapWidgets
)
