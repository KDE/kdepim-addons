# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kaddressbook_searchduplicatesplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kaddressbook/mainview)
target_sources(kaddressbook_searchduplicatesplugin PRIVATE
    searchduplicatesplugininterface.cpp
    searchduplicatesplugin.cpp
    searchduplicatesplugininterface.h
    searchduplicatesplugin.h
)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_searchduplicatesplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kaddressbook_searchduplicatesplugin
  KPim${KF_MAJOR_VERSION}::PimCommon KF${KF_MAJOR_VERSION}::Completion  KPim${KF_MAJOR_VERSION}::PimCommonAkonadi KF${KF_MAJOR_VERSION}::XmlGui kaddressbookmergelibprivate KF${KF_MAJOR_VERSION}::I18n
)
