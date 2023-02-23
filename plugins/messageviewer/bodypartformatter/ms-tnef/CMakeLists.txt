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
    KF${KF_MAJOR_VERSION}::CalendarCore
    KPim${KF_MAJOR_VERSION}::CalendarUtils
    KPim${KF_MAJOR_VERSION}::Tnef
    KF5::MessageCore
    KF5::MessageViewer
    KF${KF_MAJOR_VERSION}::IconThemes
    KF${KF_MAJOR_VERSION}::I18n
    ${TEMPLATES_LIB}
    )
install(TARGETS messageviewer_bodypartformatter_application_mstnef DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim${QT_MAJOR_VERSION}/messageviewer/bodypartformatter)
