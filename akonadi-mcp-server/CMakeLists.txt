# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"akonadimcpprotocol\")

add_executable(akonadimcpprotocol)
ecm_qt_declare_logging_category(akonadimcpprotocol HEADER akonadimcpprotocol_debug.h IDENTIFIER AKONADI_MCP_PROTOCOL_LOG
    CATEGORY_NAME org.kde.akonadimcpprotocol DESCRIPTION "akonadi mcp protocol (addressbook)" EXPORT KDEPIMADDONS
)

target_sources(
    akonadimcpprotocol
    PRIVATE
        main.cpp
        akonadimcpprotocolmanager.h
        akonadimcpprotocolmanager.cpp
        contactsearchtool/contactsearchtool.h
        contactsearchtool/contactsearchtool.cpp
        contactsearchtool/contactsearchtooljob.h
        contactsearchtool/contactsearchtooljob.cpp
        contactgroupexpandtool/contactgroupexpandtool.cpp
        contactgroupexpandtool/contactgroupexpandtool.h
        contactgroupexpandtool/contactgroupexpandtooljob.cpp
        contactgroupexpandtool/contactgroupexpandtooljob.h
        listaddressbooks/listaddressbookstool.h
        listaddressbooks/listaddressbookstool.cpp
        listaddressbooks/listaddressbookstooljob.h
        listaddressbooks/listaddressbookstooljob.cpp
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
