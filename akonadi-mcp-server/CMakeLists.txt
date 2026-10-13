# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"akonadimcpprotocol\")
add_executable(akonadimcpprotocol)

target_sources(
    akonadimcpprotocol
    PRIVATE
        main.cpp
        akonadimcpprotocolmanager.h
        akonadimcpprotocolmanager.cpp
        contactsearchtool/contactsearchtool.h
        contactsearchtool/contactsearchtool.cpp
)
target_link_libraries(
    akonadimcpprotocol
    KF6::TextAutoGenerateTextMcpProtocolCore
    KF6::I18n
    KPim6::AkonadiContactCore
)

install(
    TARGETS
        akonadimcpprotocol
        ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)
