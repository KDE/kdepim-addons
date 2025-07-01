# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(kmail_checkfoldersizeaccount INSTALL_NAMESPACE pim6/kmail/mainview)
target_sources(
    kmail_checkfoldersizeaccount
    PRIVATE
        checkfoldersizeaccountplugin.cpp
        checkfoldersizeaccountplugin.h
        checkfoldersizeaccountplugininterface.h
        checkfoldersizeaccountplugininterface.cpp
        checkfoldersizeaccountplugindialog.h
        checkfoldersizeaccountplugindialog.cpp
        checkfoldersizeaccountpluginwidget.h
        checkfoldersizeaccountpluginwidget.cpp
        checkfoldersizeaccountplugindelegate.h
        checkfoldersizeaccountplugindelegate.cpp
        checkfoldersizeaccountpluginconfiguredialog.h
        checkfoldersizeaccountpluginconfiguredialog.cpp
        checkfoldersizeaccountpluginconfigurewidget.h
        checkfoldersizeaccountpluginconfigurewidget.cpp
        checkfoldersizeaccountfilterproxymodel.h checkfoldersizeaccountfilterproxymodel.cpp
)

ecm_qt_declare_logging_category(kmail_checkfoldersizeaccount
    HEADER checkfoldersizeaccount_debug.h
    IDENTIFIER KMAIL_CHECKFOLDERSIZEACCOUNT_PLUGIN_LOG
    CATEGORY_NAME org.kde.pim.kmail_checkfoldersizeaccount
    DESCRIPTION "kdepim-addons (kmail check folder size account plugin)"
    EXPORT KDEPIMADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        kmail_checkfoldersizeaccount
        PROPERTIES UNITY_BUILD ON
    )
endif()

target_link_libraries(
    kmail_checkfoldersizeaccount
    KPim6::PimCommon
    KPim6::PimCommonAkonadi
    KF6::XmlGui
    KPim6::Libkdepim
    KF6::I18n
)
if(BUILD_TESTING)
    #add_subdirectory(autotests)
endif()
