# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_application_mstnef_plugin\")
add_library(messageviewer_bodypartformatter_application_mstnef MODULE)

target_sources(messageviewer_bodypartformatter_application_mstnef PRIVATE application_ms-tnef.cpp)

ecm_qt_declare_logging_category(messageviewer_bodypartformatter_application_mstnef HEADER ms_tnef_debug.h IDENTIFIER MS_TNEF_LOG CATEGORY_NAME org.kde.pim.ms_tnef
    DESCRIPTION "kdepim-addons (ms_tnef)"
    OLD_CATEGORY_NAMES log_ms_tnef
    EXPORT KDEPIMADDONS
    )



target_link_libraries(messageviewer_bodypartformatter_application_mstnef
    Qt::Core
    KF6::CalendarCore
    KPim6::CalendarUtils
    KPim6::Tnef
    KPim6::MessageCore
    KPim6::MessageViewer
    KF6::IconThemes
    KF6::I18n
    KF6::TextTemplate
    )
install(TARGETS messageviewer_bodypartformatter_application_mstnef DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim6/messageviewer/bodypartformatter)
