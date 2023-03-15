# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    )

kcoreaddons_add_plugin(kaddressbook_sendmailplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kaddressbook/mainview)

target_sources(kaddressbook_sendmailplugin PRIVATE
    sendmailplugininterface.cpp
    sendmailplugin.cpp
    mailsenderjob.cpp
    sendmailplugininterface.h
    sendmailplugin.h
    mailsenderjob.h
    )

ecm_qt_declare_logging_category(kaddressbook_sendmailplugin HEADER kaddressbook_sendmailplugin_debug.h IDENTIFIER KADDRESSBOOK_SENDMAIL_LOG CATEGORY_NAME org.kde.pim.kaddressbook_sendmail
    DESCRIPTION "kdepim-addons (kaddressbook send mail plugin)"
    OLD_CATEGORY_NAMES log_kaddressbook_sendmail
    EXPORT KDEPIMADDONS
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_sendmailplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kaddressbook_sendmailplugin
    KPim${KF_MAJOR_VERSION}::PimCommon KF${KF_MAJOR_VERSION}::Completion  KPim${KF_MAJOR_VERSION}::PimCommonAkonadi KF${KF_MAJOR_VERSION}::XmlGui KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::Codecs
    )

if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()

