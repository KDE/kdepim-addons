# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_library(
    kcm_akonadi_mcp_protocol
    MODULE
    kcm_akonadimcpserver.cpp
    kcm_akonadimcpserver.h
)
target_link_libraries(
    kcm_akonadi_mcp_protocol
    KF6::CoreAddons
    KF6::KCMUtils
    KF6::I18n
    KF6::TextAutoGenerateTextMcpProtocolWidgets
    Qt::DBus
)

install(TARGETS kcm_akonadi_mcp_protocol DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim6/kcms/akonadimcpserver/)
