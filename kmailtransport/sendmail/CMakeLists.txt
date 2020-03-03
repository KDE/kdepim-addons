set(mailtransport_sendplugin_SRCS
    sendmailtransportplugin.cpp
    sendmailjob.cpp
    sendmailconfigwidget.cpp
    sendmailconfigdialog.cpp
    )

if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(mailtransport_sendplugin_SRCS HEADER sendmailplugin_debug.h IDENTIFIER MAILTRANSPORT_PLUGIN_LOG CATEGORY_NAME org.kde.pim.mailtransport_sendmail)
else()
    ecm_qt_declare_logging_category(mailtransport_sendplugin_SRCS HEADER sendmailplugin_debug.h IDENTIFIER MAILTRANSPORT_PLUGIN_LOG CATEGORY_NAME org.kde.pim.mailtransport_sendmail
        DESCRIPTION "kdepim-addons (kmailtransport sendmail plugin)"
        EXPORT KDEPIMADDONS
        )
endif()


ki18n_wrap_ui(mailtransport_sendplugin_SRCS
    sendmailsettings.ui
    )

kcoreaddons_add_plugin(mailtransport_sendplugin JSON sendmailtransport.json SOURCES
    ${mailtransport_sendplugin_SRCS} INSTALL_NAMESPACE mailtransport)

target_link_libraries(mailtransport_sendplugin
    KF5::MailTransport
    KF5::CoreAddons
    KF5::I18n
    KF5::ConfigWidgets
    KF5::KIOWidgets
    )
