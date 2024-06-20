# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"kmailtransport_plugins\")
if(NOT WIN32)
    add_subdirectory(sendmail)
endif()
