# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set(messageviewer_adblock_lib_common_SRCS)
ecm_qt_declare_logging_category(messageviewer_adblock_lib_common_SRCS HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME org.kde.pim.adblockinterceptor)

set(adblocklibprivate_widget_SRCS
    widgets/adblockblockableitemsdialog.cpp
    widgets/adblockblockableitemswidget.cpp
    widgets/adblockcreatefilterdialog.cpp
    widgets/adblockpluginurlinterceptorconfigurewidget.cpp
    widgets/adblockpluginurlinterceptorconfiguredialog.cpp
    widgets/adblockaddsubscriptiondialog.cpp
    widgets/adblockautomaticruleslistwidget.cpp
    widgets/adblocklistwidget.cpp
    widgets/adblocksettingwidget.cpp
    widgets/adblockshowlistdialog.cpp
    )

set(adblocklibprivate_job_SRCS
    adblockblockableitemsjob.cpp
    )

set(adblocklibprivate_SRCS
    adblockmanager.cpp
    adblocksearchtree.cpp
    adblockrule.cpp
    adblockregexp.cpp
    adblockutil.cpp
    adblockmatcher.cpp
    adblocksubscription.cpp
    ${adblocklibprivate_widget_SRCS}
    ${messageviewer_adblock_lib_common_SRCS}
    ${adblocklibprivate_job_SRCS}
    )

kconfig_add_kcfg_files(adblocklibprivate_SRCS
    settings/globalsettings_webengineurlinterceptoradblock.kcfgc
    )


ki18n_wrap_ui(adblocklibprivate_SRCS widgets/ui/adblockcreatefilterwidget.ui widgets/ui/settings_adblock.ui)

add_library(adblocklibprivate ${adblocklibprivate_SRCS})
generate_export_header(adblocklibprivate BASE_NAME adblocklib)

target_link_libraries(adblocklibprivate
    PRIVATE
    Qt::Core
    Qt::WebEngine
    Qt::WebEngineWidgets
    KF5::I18n
    KF5::ItemViews
    KF5::ConfigCore
    KF5::PimCommon
    KF5::KIOWidgets
    KF5::WebEngineViewer
    KF5::TextWidgets
    KF5::PimTextEdit
    KF5::Libkdepim
    KF5::SyntaxHighlighting
    )

set_target_properties(adblocklibprivate
    PROPERTIES VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )

install(TARGETS adblocklibprivate ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()
