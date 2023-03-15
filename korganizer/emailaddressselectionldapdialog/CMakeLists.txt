# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#if(BUILD_TESTING)
#    add_subdirectory(tests)
#    add_subdirectory(autotests)
#endif()

kcoreaddons_add_plugin(emailaddressselectionldapdialogplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/akonadi)
target_sources(emailaddressselectionldapdialogplugin PRIVATE
    emailaddressselectionldapdialog.cpp
    emailaddressselectionldapdialog.h
    )


target_link_libraries(emailaddressselectionldapdialogplugin
    KF${KF_MAJOR_VERSION}::I18n KPim${KF_MAJOR_VERSION}::AkonadiContact KPim${KF_MAJOR_VERSION}::PimCommonAkonadi
    )
