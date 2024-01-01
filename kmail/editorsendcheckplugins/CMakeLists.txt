# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_definitions(-DTRANSLATION_DOMAIN=\"kmail_editorsendcheck_plugins\")
add_subdirectory(confirm-address)
add_subdirectory(checkbeforesend)
add_subdirectory(automaticaddcontacts)
