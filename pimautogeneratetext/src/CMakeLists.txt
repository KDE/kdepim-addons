# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_library(KPim6AutoGenerateText)
generate_export_header(KPim6AutoGenerateText BASE_NAME PimAutoGenerateText)

ecm_qt_declare_logging_category(KPim6AutoGenerateText HEADER pimautogeneratetext_debug.h IDENTIFIER PIMAUTOGENERATE_LOG CATEGORY_NAME org.kde.pim.pimautogeneratetext
    DESCRIPTION "kdepim-addons (pimautogeneratetext lib)"
    EXPORT KDEPIMADDONS
)

add_library(KPim6::AutoGenerateText ALIAS KPim6AutoGenerateText)

target_sources(KPim6AutoGenerateText PRIVATE
    autogenerateconfigurelistview.h
    autogenerateconfigurelistview.cpp

    autogenerateconfigureaskinfo.h
    autogenerateconfigureaskinfo.cpp

    autogenerateconfigureaskmodel.h
    autogenerateconfigureaskmodel.cpp

    pimautogeneratetext_private_export.h

    autogenerateconfigureaskutils.h
    autogenerateconfigureaskutils.cpp

    autogenerateconfigureaskmanager.h
    autogenerateconfigureaskmanager.cpp

    autogenerateconfigureaskmenu.h
    autogenerateconfigureaskmenu.cpp

    autogenerateconfigureaskdialog.h
    autogenerateconfigureaskdialog.cpp

    autogenerateconfigureaskwidget.h
    autogenerateconfigureaskwidget.cpp

    autogenerateconfigurelistviewdelegate.h
    autogenerateconfigurelistviewdelegate.cpp
)

ecm_generate_headers(PimAutoGenerateText_Camelcases_HEADERS
    HEADER_NAMES
    AutogenerateConfigureAskMenu
    AutogenerateConfigureAskManager
    REQUIRED_HEADERS PimAutoGenerateText_HEADERS
    PREFIX PimAutoGenerateText
)

target_link_libraries(KPim6AutoGenerateText
    PUBLIC
    Qt::Widgets
    PRIVATE
    KF6::I18n
    KF6::ConfigGui
    KF6::WidgetsAddons
    KF6::TextAutoGenerateText
)

set_target_properties(KPim6AutoGenerateText PROPERTIES
    VERSION ${KDEPIMADDONS_LIB_VERSION}
    SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
)

install(TARGETS KPim6AutoGenerateText ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

