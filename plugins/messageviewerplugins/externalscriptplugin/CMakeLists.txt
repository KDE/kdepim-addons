# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_externalscriptplugin
    INSTALL_NAMESPACE pim6/messageviewer/viewerplugin)
target_sources(messageviewer_externalscriptplugin PRIVATE
    viewerpluginexternalscript.cpp
    viewerpluginexternalscriptinterface.cpp
    viewerpluginexternalscriptmanager.cpp
    viewerpluginexternalscriptinfo.cpp
    viewerpluginexternalscriptsloadjob.cpp
    viewerpluginexternalscriptparseargument.cpp
    configuredialog/viewerpluginexternalconfiguredialog.cpp
    configuredialog/viewerpluginexternalconfigurewidget.cpp
    configuredialog/viewerpluginexternaleditdialog.cpp
    configuredialog/viewerpluginexternaleditwidget.cpp

    viewerpluginexternalscript.h
    viewerpluginexternalscriptinterface.h
    viewerpluginexternalscriptmanager.h
    viewerpluginexternalscriptinfo.h
    viewerpluginexternalscriptsloadjob.h
    viewerpluginexternalscriptparseargument.h
    configuredialog/viewerpluginexternalconfiguredialog.h
    configuredialog/viewerpluginexternalconfigurewidget.h
    configuredialog/viewerpluginexternaleditdialog.h
    configuredialog/viewerpluginexternaleditwidget.h
    )


ecm_qt_declare_logging_category(messageviewer_externalscriptplugin HEADER externalscriptplugin_debug.h IDENTIFIER EXTERNALSCRIPTPLUGIN_LOG CATEGORY_NAME org.kde.pim.externalscriptplugin
    DESCRIPTION "kdepim-addons (External Script Plugin)"
    OLD_CATEGORY_NAMES log_externalscriptplugin
    EXPORT KDEPIMADDONS
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_externalscriptplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_externalscriptplugin
    KPim6::MessageViewer KF6::XmlGui KF6::I18n KPim6::PimCommon KF6::KIOWidgets KPim6::Libkdepim
    )

if (KDEPIMADDONS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif() 

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
