# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_askautogeneratetexteditorplugin INSTALL_NAMESPACE pim6/kmail/plugineditor)
target_sources(kmail_askautogeneratetexteditorplugin PRIVATE
    askautogeneratetextplugineditor.cpp
    askautogeneratetextplugineditor.h
    askautogeneratetextplugineditorinterface.h
    askautogeneratetextplugineditorinterface.cpp
)

ecm_qt_declare_logging_category(kmail_askautogeneratetexteditorplugin HEADER changecaseeditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_CHANGECASE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_askautogeneratetexteditorplugin
    DESCRIPTION "kdepim-addons (kmail AI editor plugins)"
    OLD_CATEGORY_NAMES log_kmail_askautogeneratetexteditorplugin
    EXPORT KDEPIMADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_askautogeneratetexteditorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_askautogeneratetexteditorplugin
    KPim6::MessageComposer KF6::XmlGui KF6::I18n
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

