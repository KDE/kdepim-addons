# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(kmail_antispamplugin INSTALL_NAMESPACE pim6/kmail/mainview)
target_sources(kmail_antispamplugin PRIVATE
    antispamplugin.cpp
    antispamplugininterface.cpp
    ../common/antispamwizard.cpp
    ../common/antispam.qrc
    antispamplugin.h
    antispamplugininterface.h
    ../common/antispamwizard.h
)

target_link_libraries(kmail_antispamplugin
  KPim6::PimCommonAkonadi KF6::Completion KPim6::MailCommon KF6::XmlGui KF6::I18n KF6::GuiAddons
)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_antispamplugin PROPERTIES UNITY_BUILD ON)
endif()


if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()
