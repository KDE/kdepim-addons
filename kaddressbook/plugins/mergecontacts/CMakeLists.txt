# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kaddressbook_mergecontactsplugin INSTALL_NAMESPACE pim6/kaddressbook/mainview)
target_sources(
    kaddressbook_mergecontactsplugin
    PRIVATE
        mergecontactsplugininterface.cpp
        mergecontactsplugin.cpp
        mergecontactsplugininterface.h
        mergecontactsplugin.h
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        kaddressbook_mergecontactsplugin
        PROPERTIES UNITY_BUILD ON
    )
endif()

target_link_libraries(
    kaddressbook_mergecontactsplugin
    KPim6::PimCommon
    KF6::Completion
    KPim6::PimCommonAkonadi
    KF6::XmlGui
    kaddressbookmergelibprivate
    KF6::I18n
)
