# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(kmail_antivirusplugin SOURCES
    ${kmail_antivirusplugin_SRCS} INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kmail/mainview)

target_sources(kmail_antivirusplugin PRIVATE
    antivirusplugin.cpp
    antivirusplugininterface.cpp
    ../common/antispamwizard.cpp
    ../common/antispam.qrc
    antivirusplugin.h
    antivirusplugininterface.h
    ../common/antispamwizard.h
)


target_link_libraries(kmail_antivirusplugin
  KF5::PimCommonAkonadi KF${KF_MAJOR_VERSION}::Completion KPim${KF_MAJOR_VERSION}::MailCommon KF5::AkonadiWidgets KF${KF_MAJOR_VERSION}::XmlGui KPim${KF_MAJOR_VERSION}::Libkdepim KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::GuiAddons
)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_antivirusplugin PROPERTIES UNITY_BUILD ON)
endif()

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()
