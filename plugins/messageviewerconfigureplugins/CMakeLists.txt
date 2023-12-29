# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"messageviewerconfiguresettingsplugins\")

add_subdirectory(gravatar)

add_subdirectory(dkim-verify)
add_subdirectory(expireaccounttrashfolder)
add_subdirectory(foldersettings)
add_subdirectory(openurlwith)
