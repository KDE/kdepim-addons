# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"messageviewerconfiguresettingsplugins\")

add_subdirectory(gravatar)

set(CMAKE_REQUIRED_LIBRARIES KF5::MessageViewer)
add_subdirectory(dkim-verify)
add_subdirectory(expireaccounttrashfolder)
add_subdirectory(foldersettings)
