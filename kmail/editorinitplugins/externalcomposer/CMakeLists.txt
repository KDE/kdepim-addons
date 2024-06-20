# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_externalcomposereditorplugin  INSTALL_NAMESPACE pim6/kmail/plugineditorinit)
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

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_externalcomposereditorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_externalcomposereditorplugin
    KPim6::MessageComposer KF6::XmlGui KF6::I18n KF6::KIOWidgets
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

