# SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_definitions(-DTRANSLATION_DOMAIN=\"kmail_editorconvertertext_plugins\")
if(discount_FOUND)
    add_subdirectory(markdown)
endif()
