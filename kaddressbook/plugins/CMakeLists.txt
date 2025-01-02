# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_definitions(-DTRANSLATION_DOMAIN=\"kaddressbook_plugins\")

add_subdirectory(mergelib)
add_subdirectory(mergecontacts)
add_subdirectory(searchduplicates)
add_subdirectory(sendvcards)
add_subdirectory(sendmail)
add_subdirectory(checkgravatar)
