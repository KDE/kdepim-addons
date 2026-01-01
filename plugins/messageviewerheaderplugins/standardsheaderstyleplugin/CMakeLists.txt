# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_standardsheaderstyleplugin INSTALL_NAMESPACE pim6/messageviewer/headerstyle)
target_sources(
    messageviewer_standardsheaderstyleplugin
    PRIVATE
        standardsheaderstyleplugin.cpp
        standardsheaderstyleinterface.cpp
        standardheaderstrategy.cpp
        standardsheaderstyleplugin.h
        standardsheaderstyleinterface.h
        standardheaderstrategy.h
)

target_link_libraries(
    messageviewer_standardsheaderstyleplugin
    KPim6::MessageViewer
    KF6::XmlGui
    KF6::I18n
    KPim6::GrantleeTheme
)
