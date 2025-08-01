# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(mailtransport_sendplugin INSTALL_NAMESPACE "pim6/mailtransport")

target_sources(
    mailtransport_sendplugin
    PRIVATE
        sendmailtransportplugin.cpp
        sendmailjob.cpp
        sendmailconfigwidget.cpp
        sendmailconfigdialog.cpp
        sendmailtransportplugin.h
        sendmailjob.h
        sendmailconfigwidget.h
        sendmailconfigdialog.h
)

ecm_qt_declare_logging_category(mailtransport_sendplugin HEADER sendmailplugin_debug.h IDENTIFIER MAILTRANSPORT_PLUGIN_LOG CATEGORY_NAME org.kde.pim.mailtransport_sendmail
    DESCRIPTION "kdepim-addons (kmailtransport sendmail plugin)"
    EXPORT KDEPIMADDONS
)

ki18n_wrap_ui(mailtransport_sendplugin
    sendmailsettings.ui
)
if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(mailtransport_sendplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(
    mailtransport_sendplugin
    KPim6::MailTransport
    KF6::CoreAddons
    KF6::I18n
    KF6::ConfigWidgets
    KF6::KIOWidgets
)
