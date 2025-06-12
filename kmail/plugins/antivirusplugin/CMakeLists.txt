# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(kmail_antivirusplugin SOURCES
    ${kmail_antivirusplugin_SRCS} INSTALL_NAMESPACE pim6/kmail/mainview
)

target_sources(
    kmail_antivirusplugin
    PRIVATE
        antivirusplugin.cpp
        antivirusplugininterface.cpp
        ../common/antispamwizard.cpp
        ../common/antispam.qrc
        antivirusplugin.h
        antivirusplugininterface.h
        ../common/antispamwizard.h
)

target_link_libraries(
    kmail_antivirusplugin
    KPim6::PimCommonAkonadi
    KF6::Completion
    KPim6::MailCommon
    KPim6::AkonadiWidgets
    KF6::XmlGui
    KPim6::Libkdepim
    KF6::I18n
    KF6::GuiAddons
)
if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_antivirusplugin PROPERTIES UNITY_BUILD ON)
endif()

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
