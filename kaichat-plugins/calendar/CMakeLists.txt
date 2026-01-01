# SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_definitions(-DTRANSLATION_DOMAIN=\"kaichat_calendar\")

kcoreaddons_add_plugin(kaichat_calendarplugin INSTALL_NAMESPACE autogeneratetext/toolplugins)

ecm_qt_declare_logging_category(kaichat_calendarplugin HEADER kaichat_calendarplugin_debug.h IDENTIFIER KAICHAT_CALENDAR_LOG
    CATEGORY_NAME org.kde.kaichat_calendarplugin DESCRIPTION "kaichat (calendar)" EXPORT KDEPIMADDONS
)

target_sources(
    kaichat_calendarplugin
    PRIVATE
    kaichatcalendarplugin.cpp
    kaichatcalendarplugin.h
    kaichatcalendarplugindialog.cpp
    kaichatcalendarplugindialog.h
    kaichatcalendarpluginwidget.cpp
    kaichatcalendarpluginwidget.h
    kaichatcalendarpluginjob.h
    kaichatcalendarpluginjob.cpp
    kaichatcalendarpluginutils.cpp
    kaichatcalendarpluginutils.h
)
target_link_libraries(kaichat_calendarplugin KF6::TextAutoGenerateText KPim6::AkonadiContactCore)
