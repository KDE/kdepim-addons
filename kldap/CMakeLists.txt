# SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"kldap_plugins\")
if(KDEPIM_ADDONS_HAVE_ACTIVITY_SUPPORT)
    add_subdirectory(activities)
endif()
