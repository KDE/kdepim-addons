# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_nonbreakingspaceeditorplugin INSTALL_NAMESPACE kmail/plugineditor)
target_sources(kmail_nonbreakingspaceeditorplugin PRIVATE
    nonbreakingspaceplugineditor.cpp
    nonbreakingspaceplugineditorinterface.cpp
)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_nonbreakingspaceeditorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_nonbreakingspaceeditorplugin
  KF5::MessageComposer KF5::XmlGui KF5::I18n
)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

