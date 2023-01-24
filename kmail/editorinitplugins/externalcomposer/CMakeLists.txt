# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_externalcomposereditorplugin  INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kmail/plugineditorinit)
target_sources(kmail_externalcomposereditorplugin PRIVATE
    externalcomposerplugineditor.cpp
    externalcomposerplugineditorinterface.cpp
    externalcomposerconfiguredialog.cpp
    externalcomposerconfigurewidget.cpp
    externalcomposerplugineditor.h
    externalcomposerplugineditorinterface.h
    externalcomposerconfiguredialog.h
    externalcomposerconfigurewidget.h
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_externalcomposereditorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_externalcomposereditorplugin
    KF5::MessageComposer KF${KF_MAJOR_VERSION}::XmlGui KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::KIOWidgets
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

