# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_insertemaileditorplugin INSTALL_NAMESPACE kmail/plugineditor)
target_sources(kmail_insertemaileditorplugin PRIVATE
    insertemailplugineditor.cpp
    insertemailplugineditorinterface.cpp
    selectmailwidget.cpp
    selectmaildialog.cpp
)


target_link_libraries(kmail_insertemaileditorplugin
  KF5::MessageComposer KF5::XmlGui KF5::I18n KF5::AkonadiContact
)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_insertemaileditorplugin PROPERTIES UNITY_BUILD ON)
endif()

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

