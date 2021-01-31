add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_application_gnupgwks_plugin\")

set(messageviewer_bodypartformatter_application_gnupgwks_SRCS
    plugin.cpp
    gnupgwksformatter.cpp
    gnupgwksurlhandler.cpp
    gnupgwksmessagepart.cpp
    pgpkeyformatter.cpp
    pgpkeymemento.cpp
    pgpkeymessagepart.cpp
    pgpkeyurlhandler.cpp
    )

qt5_add_resources(messageviewer_bodypartformatter_application_gnupgwks_SRCS templates.qrc)

ecm_qt_declare_logging_category(messageviewer_bodypartformatter_application_gnupgwks_SRCS
    HEADER gnupgwks_debug.h
    IDENTIFIER GNUPGWKS_LOG
    CATEGORY_NAME org.kde.pim.gnupgwks
    DESCRIPTION "kdepim-addons (OpenPGP and GnuPG WKS body part formatter plugin)"
    EXPORT KDEPIMADDONS
    )


add_library(messageviewer_bodypartformatter_application_gnupgwks MODULE ${messageviewer_bodypartformatter_application_gnupgwks_SRCS})
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_bodypartformatter_application_gnupgwks PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_bodypartformatter_application_gnupgwks
    Qt::Core
    KF5::MessageCore
    KF5::MessageViewer
    KF5::MailTransportAkonadi
    KF5::GrantleeTheme
    KF5::I18n
    KF5::Mime
    KF5::IdentityManagement
    Grantlee5::Templates
    Gpgmepp
    )
install(TARGETS messageviewer_bodypartformatter_application_gnupgwks DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)
