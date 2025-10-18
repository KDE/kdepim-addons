# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_definitions(-DTRANSLATION_DOMAIN=\"kaichat_addressbook\")

kcoreaddons_add_plugin(kaichat_addressbookplugin INSTALL_NAMESPACE autogeneratetext/toolplugins)

ecm_qt_declare_logging_category(kaichat_addressbookplugin HEADER kaichat_addressbookplugin_debug.h IDENTIFIER KAICHAT_ADDRESSBOOK_LOG
    CATEGORY_NAME org.kde.kaichat_addressbookplugin DESCRIPTION "kaichat (addressbook)" EXPORT KDEPIMADDONS
)

target_sources(
    kaichat_addressbookplugin
    PRIVATE

)
target_link_libraries(kaichat_addressbookplugin KF6::TextAutoGenerateText)
