# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kaddressbook_searchduplicatesplugin INSTALL_NAMESPACE kaddressbook/mainview)
target_sources(kaddressbook_searchduplicatesplugin PRIVATE
    searchduplicatesplugininterface.cpp
    searchduplicatesplugin.cpp
)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_searchduplicatesplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kaddressbook_searchduplicatesplugin
  KF5::PimCommon KF5::Completion  KF5::PimCommonAkonadi KF5::XmlGui kaddressbookmergelibprivate KF5::I18n
)
