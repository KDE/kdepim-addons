# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"akonadimcpprotocol\")

add_executable(
    akonadimcpprotocol
    mailsearch/searchmailtooljob.h
    mailsearch/searchmailtooljob.cpp
)
ecm_qt_declare_logging_category(akonadimcpprotocol HEADER akonadimcpprotocol_debug.h IDENTIFIER AKONADI_MCP_PROTOCOL_LOG
    CATEGORY_NAME org.kde.akonadimcpprotocol DESCRIPTION "akonadi mcp protocol" EXPORT KDEPIMADDONS
)

target_sources(
    akonadimcpprotocol
    PRIVATE
        main.cpp
        akonadimcpprotocolmanager.h
        akonadimcpprotocolmanager.cpp
        common/tooljobbase.h
        common/tooljobbase.cpp
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
        upcomingbirthdaystool/upcomingbirthdaystool.h
        upcomingbirthdaystool/upcomingbirthdaystool.cpp
        upcomingbirthdaystool/upcomingbirthdaystooljob.h
        upcomingbirthdaystool/upcomingbirthdaystooljob.cpp
        calendarcommon/calendartoolutils.h
        calendarcommon/calendartoolutils.cpp
        calendarcommon/calendartooljobbase.h
        calendarcommon/calendartooljobbase.cpp
        calendareventstool/calendareventstool.h
        calendareventstool/calendareventstool.cpp
        calendareventstool/calendareventstooljob.h
        calendareventstool/calendareventstooljob.cpp
        freebusytool/freebusytool.h
        freebusytool/freebusytool.cpp
        freebusytool/freebusytooljob.h
        freebusytool/freebusytooljob.cpp
        todolisttool/todolisttool.h
        todolisttool/todolisttool.cpp
        todolisttool/todolisttooljob.h
        todolisttool/todolisttooljob.cpp
        akonadiresourcesstatus/akonadiresourcesstatustool.h
        akonadiresourcesstatus/akonadiresourcesstatustool.cpp
        createcontacttool/createcontacttool.h
        createcontacttool/createcontacttool.cpp
        createcontacttool/createcontacttooljob.h
        createcontacttool/createcontacttooljob.cpp
        mailsearch/searchmailtool.h
        mailsearch/searchmailtool.cpp
)
target_link_libraries(
    akonadimcpprotocol
    KF6::TextAutoGenerateTextMcpProtocolCore
    KF6::I18n
    KPim6::AkonadiContactCore
    KPim6::AkonadiCalendar
    KF6::CalendarCore
)

install(
    TARGETS
        akonadimcpprotocol
        ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)
