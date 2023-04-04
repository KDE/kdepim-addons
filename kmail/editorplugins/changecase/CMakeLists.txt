# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_changecaseeditorplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kmail/plugineditor)
target_sources(kmail_changecaseeditorplugin PRIVATE
    changecaseplugineditor.cpp
    changecaseplugineditorinterface.cpp
    changecaseplugineditor.h
    changecaseplugineditorinterface.h
    )

ecm_qt_declare_logging_category(kmail_changecaseeditorplugin HEADER changecaseeditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_CHANGECASE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_changecaseeditorplugin
    DESCRIPTION "kdepim-addons (kmail changecase editor plugins)"
    OLD_CATEGORY_NAMES log_kmail_changecaseeditorplugin
    EXPORT KDEPIMADDONS
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_changecaseeditorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_changecaseeditorplugin
    KPim6::MessageComposer KF6::XmlGui KF6::I18n
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

