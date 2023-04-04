# SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_openurlwithconfigplugin INSTALL_NAMESPACE pim6/messageviewer/configuresettings)
target_sources(messageviewer_openurlwithconfigplugin PRIVATE
    openurlwithconfigplugin.cpp
    openurlwithconfigplugin.h
    )


target_link_libraries(messageviewer_openurlwithconfigplugin
    KPim6::MessageViewer
    KF6::I18n
    KF6::KIOWidgets
    openurlwithconfigure
    )


add_library(openurlwithconfigure)
target_sources(openurlwithconfigure PRIVATE
    openurlwithconfiguredialog.h
    openurlwithconfiguredialog.cpp
    openurlwithconfigurewidget.h
    openurlwithconfigurewidget.cpp
    openurlwith_private_export.h
    openurlwithconfigurecreatedialog.h
    openurlwithconfigurecreatedialog.cpp
    openurlwithconfigurecreatewidget.h
    openurlwithconfigurecreatewidget.cpp
    )

ecm_qt_declare_logging_category(openurlwithconfigure HEADER libopenurlwithconfigure_debug.h IDENTIFIER LIBOPENURLWITHCONFIGURE_PLUGIN_LOG
    CATEGORY_NAME org.kde.pim.libopenurlwithconfigureplugin
    DESCRIPTION "kdepim-addons (open url with plugin)"
    EXPORT KDEPIMADDONS
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(openurlwithconfigure PROPERTIES UNITY_BUILD ON)
endif()

generate_export_header(openurlwithconfigure BASE_NAME libopenurlwithconfigure)
target_link_libraries(openurlwithconfigure
    KF6::I18n
    KPim6::MessageViewer
    KF6::KIOWidgets
    KF6::ItemViews
    KPim6::Libkdepim
    )

set_target_properties(openurlwithconfigure
    PROPERTIES OUTPUT_NAME openurlwithconfigure VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )

install(TARGETS openurlwithconfigure ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)
if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
