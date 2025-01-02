# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_insertemaileditorplugin INSTALL_NAMESPACE pim6/kmail/plugineditor)
target_sources(kmail_insertemaileditorplugin PRIVATE
    insertemailplugineditor.cpp
    insertemailplugineditorinterface.cpp
    selectmailwidget.cpp
    selectmaildialog.cpp
    insertemailplugineditor.h
    insertemailplugineditorinterface.h
    selectmailwidget.h
    selectmaildialog.h
)


target_link_libraries(kmail_insertemaileditorplugin
  KPim6::MessageComposer KF6::XmlGui KF6::I18n KPim6::AkonadiContactCore
)
if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_insertemaileditorplugin PROPERTIES UNITY_BUILD ON)
endif()

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

