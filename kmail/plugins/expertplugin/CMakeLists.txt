# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(kmail_expertplugin INSTALL_NAMESPACE pim6/kmail/mainview)
target_sources(
    kmail_expertplugin
    PRIVATE
        expertplugin.cpp
        expertplugininterface.cpp
        expertplugin.h
        expertplugininterface.h
)

ecm_qt_declare_logging_category(kmail_expertplugin
    HEADER expertplugin_debug.h
    IDENTIFIER KMAIL_EXPERT_PLUGIN_LOG
    CATEGORY_NAME org.kde.pim.kmail_expertplugin
    DESCRIPTION "kdepim-addons (kmail expert plugin)"
    EXPORT KDEPIMADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_expertplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(
    kmail_expertplugin
    KPim6::PimCommon
    KPim6::PimCommonAkonadi
    KF6::XmlGui
    KPim6::Libkdepim
    KF6::I18n
)
if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
