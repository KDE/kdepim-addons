# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_definitions(-DTRANSLATION_DOMAIN=\"kmail_editor_plugins\")
add_subdirectory(insertspecialcharacter)
add_subdirectory(changecase)
add_subdirectory(zoomtext)
add_subdirectory(nonbreakingspace)
add_subdirectory(autocorrection)
add_subdirectory(insertemail)
add_subdirectory(insertshorturl)
add_subdirectory(sharetext)
add_subdirectory(qtcreator-template)
add_subdirectory(quicktext)
