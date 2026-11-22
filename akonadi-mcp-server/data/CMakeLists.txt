# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

install(FILES org.kde.akonadimcpprotocol.desktop DESTINATION ${KDE_INSTALL_AUTOSTARTDIR})
if(AKONADI_MCP_INSTALL_NOTIFYRC)
    install(FILES akonadimcpprotocol.notifyrc DESTINATION ${KDE_INSTALL_KNOTIFYRCDIR})
endif()
