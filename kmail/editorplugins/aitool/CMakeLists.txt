# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_aitooleditorplugin INSTALL_NAMESPACE pim6/kmail/plugineditor)
target_sources(kmail_aitooleditorplugin PRIVATE
    aitooltextplugineditor.cpp
    aitooltextplugineditor.h
    aitooltextplugineditorinterface.h
    aitooltextplugineditorinterface.cpp
)

ecm_qt_declare_logging_category(kmail_aitooleditorplugin HEADER aitooleditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_AITOOL_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_aitooleditorplugin
    DESCRIPTION "kdepim-addons (kmail AI chat tool plugins)"
    EXPORT KDEPIMADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_aitooleditorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_aitooleditorplugin
    KPim6::MessageComposer KF6::XmlGui KF6::I18n KPim6::AutoGenerateText KF6::TextAutoGenerateText
)

