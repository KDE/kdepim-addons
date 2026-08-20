# SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

include_directories(${CMAKE_CURRENT_BINARY_DIR})
kcoreaddons_add_plugin(kldapactivitiesplugin INSTALL_NAMESPACE "pim6/ldapactivities")

target_sources(
    kldapactivitiesplugin
    PRIVATE
        ldapactivitiesplugin.h
        ldapactivitiesplugin.cpp
)

target_link_libraries(
    kldapactivitiesplugin
    KF6::CoreAddons
    Qt::Widgets
    KPim6::PimCommonActivities
    KPim6::LdapWidgets
)
