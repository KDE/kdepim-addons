# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_briefheaderstyleplugin INSTALL_NAMESPACE pim6/messageviewer/headerstyle)
target_sources(
    messageviewer_briefheaderstyleplugin
    PRIVATE
        briefheaderstyleplugin.cpp
        briefheaderstyleinterface.cpp
        briefheaderstyle.cpp
        briefheaderstrategy.cpp
        briefheaderstyleplugin.h
        briefheaderstyleinterface.h
        briefheaderstyle.h
        briefheaderstrategy.h
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        messageviewer_briefheaderstyleplugin
        PROPERTIES UNITY_BUILD ON
    )
endif()

target_link_libraries(
    messageviewer_briefheaderstyleplugin
    KPim6::MessageViewer
    KF6::XmlGui
    KF6::I18n
)
