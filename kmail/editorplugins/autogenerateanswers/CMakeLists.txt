# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_autogenerateanswerseditorplugin INSTALL_NAMESPACE pim6/kmail/plugineditor)
target_sources(
    kmail_autogenerateanswerseditorplugin
    PRIVATE
        autogenerateanswerseditor.cpp
        autogenerateanswerseditor.h
        autogenerateanswerseditorinterface.h
        autogenerateanswerseditorinterface.cpp
        autogenerateanswerseditordialog.h
        autogenerateanswerseditordialog.cpp
        autogenerateanswerseditorwidget.h
        autogenerateanswerseditorwidget.cpp
        autogenerateanswerseditorutils.h
        autogenerateanswerseditorutils.cpp
        autogenerateanswerseditortextedit.h
        autogenerateanswerseditortextedit.cpp
)

ecm_qt_declare_logging_category(kmail_autogenerateanswerseditorplugin HEADER autogenerateanswerseditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_AUTOGENERATEANSWER_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_autogenerateanswerseditorplugin
    DESCRIPTION "kdepim-addons (kmail autogenerate answer plugins)"
    EXPORT KDEPIMADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        kmail_autogenerateanswerseditorplugin
        PROPERTIES UNITY_BUILD ON
    )
endif()

target_link_libraries(
    kmail_autogenerateanswerseditorplugin
    KPim6::MessageComposer
    KF6::XmlGui
    KF6::I18n
    KPim6::AutoGenerateText
    KF6::TextAutoGenerateText
)
