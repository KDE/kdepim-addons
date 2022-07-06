# SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_library(akonadidatasetools)


ecm_qt_declare_logging_category(akonadidatasetools HEADER akonadidatasetools_debug.h IDENTIFIER AKONADIDATABASETOOLS_LOG CATEGORY_NAME org.kde.pim.akonadidatabasetools
    DESCRIPTION "kdepim-addons (akonadidatabasetools)"
    EXPORT KDEPIMADDONS
)

target_sources(akonadidatasetools PRIVATE
    akonadidatabasetoolsplugin.cpp
    akonadidatabasetoolsplugin.h
    akonadidatabasetoolsplugininterface.cpp
    akonadidatabasetoolsplugininterface.h
)
generate_export_header(akonadidatasetools BASE_NAME akonadidatasetools)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(akonadidatasetools PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(akonadidatasetools
    KF5::I18n
    KF5::MessageComposer
    KF5::KIOWidgets
    KF5::XmlGui
    )

set_target_properties(akonadidatasetools
    PROPERTIES OUTPUT_NAME akonadidatasetools VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )

if(BUILD_TESTING)
   add_subdirectory(autotests)
   add_subdirectory(tests)
endif()
