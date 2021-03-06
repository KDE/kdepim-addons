# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_automaticaddcontactseditorplugin INSTALL_NAMESPACE kmail/plugincheckbeforesend)
target_sources(kmail_automaticaddcontactseditorplugin PRIVATE
    automaticaddcontactsinterface.cpp
    automaticaddcontactsplugin.cpp
    automaticaddcontactsconfigurewidget.cpp
    automaticaddcontactsjob.cpp
    automaticaddcontactstabwidget.cpp
    automaticaddcontactsconfiguretab.cpp
    automaticaddcontactsconfiguredialog.cpp
    )

ecm_qt_declare_logging_category(kmail_automaticaddcontactseditorplugin HEADER automaticaddcontactsplugin_debug.h IDENTIFIER KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_automaticaddcontactsplugin
    DESCRIPTION "kdepim-addons (Automatic add contacts plugin)"
    OLD_CATEGORY_NAMES log_kmail_automaticaddcontactsplugin
    EXPORT KDEPIMADDONS
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_automaticaddcontactseditorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_automaticaddcontactseditorplugin
    KF5::MessageComposer KF5::I18n KF5::PimCommon KF5::AkonadiContact KF5::AkonadiCore
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

