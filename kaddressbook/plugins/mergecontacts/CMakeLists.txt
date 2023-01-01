# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kaddressbook_mergecontactsplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kaddressbook/mainview)
target_sources(kaddressbook_mergecontactsplugin PRIVATE
    mergecontactsplugininterface.cpp
    mergecontactsplugin.cpp
    mergecontactsplugininterface.h
    mergecontactsplugin.h
)


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_mergecontactsplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kaddressbook_mergecontactsplugin
  KF5::PimCommon KF5::Completion  KF5::PimCommonAkonadi KF5::XmlGui kaddressbookmergelibprivate KF5::I18n
)
