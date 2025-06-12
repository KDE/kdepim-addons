# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_insertspecialcharactereditorplugin INSTALL_NAMESPACE pim6/kmail/plugineditor)
target_sources(
    kmail_insertspecialcharactereditorplugin
    PRIVATE
        insertspecialcharacterplugineditor.cpp
        insertspecialcharacterplugineditorinterface.cpp
        insertspecialcharacterplugineditor.h
        insertspecialcharacterplugineditorinterface.h
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        kmail_insertspecialcharactereditorplugin
        PROPERTIES UNITY_BUILD ON
    )
endif()

target_link_libraries(
    kmail_insertspecialcharactereditorplugin
    KPim6::MessageComposer
    KF6::XmlGui
    KF6::I18n
    KF6::TextAddonsWidgets
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
