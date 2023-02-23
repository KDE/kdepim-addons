# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(BUILD_TESTING)
    add_subdirectory(tests)
    add_subdirectory(autotests)
endif()

kcoreaddons_add_plugin(templateparseraddressrequesterplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/templateparser)

target_sources(templateparseraddressrequesterplugin PRIVATE
    templateparseremailaddressrequesterakonadi.cpp
    templateparseremailaddressrequesterakonadi.h
    )


target_link_libraries(templateparseraddressrequesterplugin
    KF5::TemplateParser KPim${KF_MAJOR_VERSION}::AkonadiContact
    )
