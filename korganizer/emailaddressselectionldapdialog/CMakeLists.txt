# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#if(BUILD_TESTING)
#    add_subdirectory(tests)
#    add_subdirectory(autotests)
#endif()

kcoreaddons_add_plugin(emailaddressselectionldapdialogplugin INSTALL_NAMESPACE pim6/akonadi)
target_sources(emailaddressselectionldapdialogplugin PRIVATE
    emailaddressselectionldapdialog.cpp
    emailaddressselectionldapdialog.h
    )


target_link_libraries(emailaddressselectionldapdialogplugin
    KF6::I18n KPim6::AkonadiContactCore KPim6::PimCommonAkonadi
    )
