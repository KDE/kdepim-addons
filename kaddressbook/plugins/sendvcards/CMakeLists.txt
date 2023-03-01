# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    )
kcoreaddons_add_plugin(kaddressbook_sendvcardsplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kaddressbook/mainview)

target_sources(kaddressbook_sendvcardsplugin PRIVATE
    sendvcardsplugininterface.cpp
    sendvcardsplugin.cpp
    sendvcardsjob.cpp
    sendvcardsplugininterface.h
    sendvcardsplugin.h
    sendvcardsjob.h
    )
ecm_qt_declare_logging_category(kaddressbook_sendvcardsplugin HEADER kaddressbook_sendvcardsplugin_debug.h IDENTIFIER KADDRESSBOOK_SENDVCARDS_LOG CATEGORY_NAME org.kde.pim.kaddressbook_sendvcards
    DESCRIPTION "kdepim-addons (kaddressbook send vcard plugin)"
    OLD_CATEGORY_NAMES log_kaddressbook_sendvcards
    EXPORT KDEPIMADDONS
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_sendvcardsplugin PROPERTIES UNITY_BUILD ON)
endif()
target_link_libraries(kaddressbook_sendvcardsplugin
    KF5::PimCommon KF${KF_MAJOR_VERSION}::Completion  KF5::PimCommonAkonadi KF${KF_MAJOR_VERSION}::XmlGui KPim${KF_MAJOR_VERSION}::MimeTreeParser KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::Service KF${KF_MAJOR_VERSION}::KIOGui
    )

if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()


