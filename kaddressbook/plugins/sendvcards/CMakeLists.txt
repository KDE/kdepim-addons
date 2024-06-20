# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)
kcoreaddons_add_plugin(kaddressbook_sendvcardsplugin INSTALL_NAMESPACE pim6/kaddressbook/mainview)

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

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_sendvcardsplugin PROPERTIES UNITY_BUILD ON)
endif()
target_link_libraries(kaddressbook_sendvcardsplugin
    KPim6::PimCommon KF6::Completion  KPim6::PimCommonAkonadi KF6::XmlGui KPim6::MimeTreeParser KF6::I18n KF6::Service KF6::KIOGui
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()


