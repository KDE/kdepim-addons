# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set(adblocksettings_gui_SRCS adblocksettings_gui.cpp)
add_executable(adblocksettings_gui ${adblocksettings_gui_SRCS})
target_link_libraries(adblocksettings_gui
    adblocklibprivate
    KF${KF_MAJOR_VERSION}::ItemViews
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::CoreAddons
    )

set(adblocksettingsdialog_gui_SRCS adblocksettingsdialog_gui.cpp)
add_executable(adblocksettingsdialog_gui ${adblocksettingsdialog_gui_SRCS})
target_link_libraries(adblocksettingsdialog_gui
    adblocklibprivate
    KF${KF_MAJOR_VERSION}::ItemViews
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::CoreAddons
    )
set(adblockautomaticruleslistwidget_gui_SRCS adblockautomaticruleslistwidget_gui.cpp adblockautomaticruleslistwidget_gui.h)
add_executable(adblockautomaticruleslistwidget_gui ${adblockautomaticruleslistwidget_gui_SRCS})
target_link_libraries(adblockautomaticruleslistwidget_gui
    adblocklibprivate
    KF${KF_MAJOR_VERSION}::ItemViews
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::CoreAddons
    )
