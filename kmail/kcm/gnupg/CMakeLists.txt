# SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_library(
    kcm_kmail_gnupgsystem
    MODULE
    kcm_gnupgsystemconfiguration.cpp
    kcm_gnupgsystemconfiguration.h
)
target_link_libraries(
    kcm_kmail_gnupgsystem
    KF6::CoreAddons
    KF6::KCMUtils
    KPim6::Libkleo
)

install(
    TARGETS kcm_kmail_gnupgsystem
    DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim6/kcms/kleopatra/
)
