# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_library(folderconfiguresettings)

target_sources(folderconfiguresettings PRIVATE
    folderconfiguresettingsdialog.cpp
    folderconfiguresettingswidget.cpp
    foldersettingfilterproxymodel.cpp
    folderconfiguretreewidget.cpp
    folderconfiguresettingspagewidget.cpp
    folderconfiguresettingsgeneralwidget.cpp
    folderconfiguresettingstemplatewidget.cpp
    folderconfiguresettingsviewwidget.cpp
    folderconfiguremodifycollectionjob.cpp
    folderconfiguresettingspagebase.cpp
    folderconfiguresettingsexperywidget.cpp
    folderconfiguresettingsdialog.h
    folderconfiguresettingswidget.h
    foldersettingfilterproxymodel.h
    folderconfiguretreewidget.h
    folderconfiguresettingspagewidget.h
    folderconfiguresettingsgeneralwidget.h
    folderconfiguresettingstemplatewidget.h
    folderconfiguresettingsviewwidget.h
    folderconfiguremodifycollectionjob.h
    folderconfiguresettingspagebase.h
    folderconfiguresettingsexperywidget.h
    )

ecm_qt_declare_logging_category(folderconfiguresettings HEADER libfolderconfiguresettings_debug.h IDENTIFIER LIBFOLDERCONFIGURESETTINGS_PLUGIN_LOG CATEGORY_NAME org.kde.pim.libfolderconfiguresettingsplugin
    DESCRIPTION "kdepim-addons (foldersettings-configure)"
    EXPORT KDEPIMADDONS
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(folderconfiguresettings PROPERTIES UNITY_BUILD ON)
endif()

generate_export_header(folderconfiguresettings BASE_NAME libfolderconfiguresettings)
target_link_libraries(folderconfiguresettings
    KPim6::MessageViewer
    KF6::I18n
    KPim6::MailCommon
    )

set_target_properties(folderconfiguresettings
    PROPERTIES OUTPUT_NAME folderconfiguresettings VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )

install(TARGETS folderconfiguresettings ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

#####
kcoreaddons_add_plugin(messageviewer_folderconfiguresettingsplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/messageviewer/configuresettings)

target_sources(messageviewer_folderconfiguresettingsplugin PRIVATE
   folderconfiguresettingsplugin.cpp
   folderconfiguresettingsplugin.h
)


target_link_libraries(messageviewer_folderconfiguresettingsplugin
  KPim6::MessageViewer
  KF6::I18n
  KPim6::MailCommon
  folderconfiguresettings
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
