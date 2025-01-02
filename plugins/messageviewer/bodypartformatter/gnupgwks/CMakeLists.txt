# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_application_gnupgwks_plugin\")

add_library(messageviewer_bodypartformatter_application_gnupgwks MODULE)
target_sources(messageviewer_bodypartformatter_application_gnupgwks PRIVATE
    plugin.cpp
    gnupgwksformatter.cpp
    gnupgwksurlhandler.cpp
    gnupgwksmessagepart.cpp
    pgpkeyformatter.cpp
    pgpkeymemento.cpp
    pgpkeymessagepart.cpp
    pgpkeyurlhandler.cpp

    plugin.h
    gnupgwksformatter.h
    gnupgwksurlhandler.h
    gnupgwksmessagepart.h
    pgpkeyformatter.h
    pgpkeymemento.h
    pgpkeymessagepart.h
    pgpkeyurlhandler.h

    templates.qrc
)

ecm_qt_declare_logging_category(messageviewer_bodypartformatter_application_gnupgwks
    HEADER gnupgwks_debug.h
    IDENTIFIER GNUPGWKS_LOG
    CATEGORY_NAME org.kde.pim.gnupgwks
    DESCRIPTION "kdepim-addons (OpenPGP and GnuPG WKS body part formatter plugin)"
    EXPORT KDEPIMADDONS
)


if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_bodypartformatter_application_gnupgwks PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_bodypartformatter_application_gnupgwks
    Qt::Core
    KPim6::MessageCore
    KPim6::MessageViewer
    KPim6::AkonadiMime
    KPim6::MailTransport
    KPim6::GrantleeTheme
    KF6::I18n
    KPim6::Mime
    KPim6::IdentityManagementCore
    KF6::TextTemplate
    Gpgmepp
)
install(TARGETS messageviewer_bodypartformatter_application_gnupgwks DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim6/messageviewer/bodypartformatter)
