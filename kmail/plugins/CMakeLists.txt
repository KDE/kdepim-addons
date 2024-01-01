# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_definitions(-DTRANSLATION_DOMAIN=\"kmail_plugins\")
add_subdirectory(antispamplugin)
add_subdirectory(antivirusplugin)
add_subdirectory(common/avscripts)
add_subdirectory(expertplugin)
add_subdirectory(mailmergeplugin)
add_subdirectory(akonadidatabasetools)

install(FILES common/kmail.antispamrc common/kmail.antivirusrc   DESTINATION ${KDE_INSTALL_CONFDIR})
