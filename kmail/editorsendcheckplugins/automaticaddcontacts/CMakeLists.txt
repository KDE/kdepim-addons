# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_automaticaddcontactseditorplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kmail/plugincheckbeforesend)
target_sources(kmail_automaticaddcontactseditorplugin PRIVATE
    automaticaddcontactsinterface.cpp
    automaticaddcontactsplugin.cpp
    automaticaddcontactsconfigurewidget.cpp
    automaticaddcontactsjob.cpp
    automaticaddcontactstabwidget.cpp
    automaticaddcontactsconfiguretab.cpp
    automaticaddcontactsconfiguredialog.cpp
    automaticaddcontactsinterface.h
    automaticaddcontactsplugin.h
    automaticaddcontactsconfigurewidget.h
    automaticaddcontactsjob.h
    automaticaddcontactstabwidget.h
    automaticaddcontactsconfiguretab.h
    automaticaddcontactsconfiguredialog.h
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
    KF5::MessageComposer KF${KF_MAJOR_VERSION}::I18n KF5::PimCommon KPim${KF_MAJOR_VERSION}::AkonadiContact KF5::AkonadiCore KF${KF_MAJOR_VERSION}::Codecs
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

