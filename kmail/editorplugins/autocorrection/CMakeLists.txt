# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_autocorrectioneditorplugin
     INSTALL_NAMESPACE pim6/kmail/plugineditor
)
target_sources(
    kmail_autocorrectioneditorplugin
    PRIVATE
        autocorrectionplugineditor.cpp
        autocorrectionplugineditorinterface.cpp
        autocorrectionplugineditor.h
        autocorrectionplugineditorinterface.h
)

target_link_libraries(
    kmail_autocorrectioneditorplugin
    KPim6::MessageComposer
    KF6::XmlGui
    KF6::I18n
)
if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        kmail_autocorrectioneditorplugin
        PROPERTIES UNITY_BUILD ON
    )
endif()

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
