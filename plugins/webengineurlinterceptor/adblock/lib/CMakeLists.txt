# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_library(adblocklibprivate ${adblocklibprivate_SRCS})
ecm_qt_declare_logging_category(adblocklibprivate HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME org.kde.pim.adblockinterceptor)

kconfig_add_kcfg_files(adblocklibprivate_kcfg_SOURCES
    settings/globalsettings_webengineurlinterceptoradblock.kcfgc
    )
target_sources(adblocklibprivate PRIVATE
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
    adblockblockableitemsjob.cpp
    adblockmanager.cpp
    adblocksearchtree.cpp
    adblockrule.cpp
    adblockregexp.cpp
    adblockutil.cpp
    adblockmatcher.cpp
    adblocksubscription.cpp
    ${adblocklibprivate_kcfg_SOURCES}

    widgets/adblockblockableitemsdialog.h
    widgets/adblockblockableitemswidget.h
    widgets/adblockcreatefilterdialog.h
    widgets/adblockpluginurlinterceptorconfigurewidget.h
    widgets/adblockpluginurlinterceptorconfiguredialog.h
    widgets/adblockaddsubscriptiondialog.h
    widgets/adblockautomaticruleslistwidget.h
    widgets/adblocklistwidget.h
    widgets/adblocksettingwidget.h
    widgets/adblockshowlistdialog.h
    adblockblockableitemsjob.h
    adblockmanager.h
    adblocksearchtree.h
    adblockrule.h
    adblockregexp.h
    adblockutil.h
    adblockmatcher.h
    adblocksubscription.h
    )



ki18n_wrap_ui(adblocklibprivate widgets/ui/adblockcreatefilterwidget.ui widgets/ui/settings_adblock.ui)

generate_export_header(adblocklibprivate BASE_NAME adblocklib)

target_link_libraries(adblocklibprivate
    PRIVATE
    Qt::Core
    
    Qt::WebEngineWidgets
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::ItemViews
    KF${KF_MAJOR_VERSION}::ConfigCore
    KF5::PimCommon
    KF${KF_MAJOR_VERSION}::KIOWidgets
    KPim${KF_MAJOR_VERSION}::WebEngineViewer
    KF${KF_MAJOR_VERSION}::TextWidgets
    KPim${KF_MAJOR_VERSION}::PimTextEdit
    KPim${KF_MAJOR_VERSION}::Libkdepim
    KF${KF_MAJOR_VERSION}::SyntaxHighlighting
    )

set_target_properties(adblocklibprivate
    PROPERTIES VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )

install(TARGETS adblocklibprivate ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()
