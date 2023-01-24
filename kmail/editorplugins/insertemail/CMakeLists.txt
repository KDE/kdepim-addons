# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_insertemaileditorplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kmail/plugineditor)
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
  KF5::MessageComposer KF${KF_MAJOR_VERSION}::XmlGui KF${KF_MAJOR_VERSION}::I18n KF5::AkonadiContact
)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_insertemaileditorplugin PROPERTIES UNITY_BUILD ON)
endif()

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

