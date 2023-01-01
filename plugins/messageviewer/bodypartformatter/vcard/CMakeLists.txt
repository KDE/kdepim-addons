# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_text_vcard_plugin\")
add_library(messageviewer_bodypartformatter_text_vcard MODULE)

target_sources(messageviewer_bodypartformatter_text_vcard PRIVATE text_vcard.cpp vcardmemento.cpp updatecontactjob.cpp vcardmemento.h updatecontactjob.h)
ecm_qt_declare_logging_category(messageviewer_bodypartformatter_text_vcard HEADER vcard_debug.h IDENTIFIER VCARD_LOG CATEGORY_NAME org.kde.pim.vcard
    DESCRIPTION "kdepim-addons (vcard)"
    OLD_CATEGORY_NAMES log_vcard
    EXPORT KDEPIMADDONS
    )


target_link_libraries(messageviewer_bodypartformatter_text_vcard  KF5::Contacts KF5::PimCommonAkonadi KF5::MessageViewer KF5::IconThemes KF5::JobWidgets KF5::I18n)
install(TARGETS messageviewer_bodypartformatter_text_vcard DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim${QT_MAJOR_VERSION}/messageviewer/bodypartformatter)
