# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(BUILD_TESTING)
    add_subdirectory(tests)
    add_subdirectory(autotests)
endif()

kcoreaddons_add_plugin(templateparseraddressrequesterplugin INSTALL_NAMESPACE pim6/templateparser)

target_sources(
    templateparseraddressrequesterplugin
    PRIVATE
        templateparseremailaddressrequesterakonadi.cpp
        templateparseremailaddressrequesterakonadi.h
)

target_link_libraries(
    templateparseraddressrequesterplugin
    KPim6::TemplateParser
    KPim6::AkonadiContactWidgets
)
