# SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_library(akonadidatasetools)


ecm_qt_declare_logging_category(akonadidatasetools HEADER akonadidatasetools_debug.h IDENTIFIER AKONADIDATABASETOOLS_LOG CATEGORY_NAME org.kde.pim.akonadidatabasetools
    DESCRIPTION "kdepim-addons (akonadidatabasetools)"
    EXPORT KDEPIMADDONS
)

target_sources(akonadidatasetools PRIVATE
    akonadidatabasetoolsplugininterface.cpp
    akonadidatabasetoolsplugininterface.h
    akonadidatabasetoolsjob.h
    akonadidatabasetoolsjob.cpp
    akonadidatabasetoolsutils.cpp
    akonadidatabasetoolsutils.h
    akonadidatabasetoolsdialog.h
    akonadidatabasetoolsdialog.cpp
    akonadidatabasetoolswidget.h
    akonadidatabasetoolswidget.cpp
)
generate_export_header(akonadidatasetools BASE_NAME akonadidatasetools)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(akonadidatasetools PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(akonadidatasetools
    KF${KF_MAJOR_VERSION}::I18n
    KF5::MessageComposer
    KF${KF_MAJOR_VERSION}::KIOWidgets
    KF${KF_MAJOR_VERSION}::XmlGui
    )

set_target_properties(akonadidatasetools
    PROPERTIES OUTPUT_NAME akonadidatasetools VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )

kcoreaddons_add_plugin(kmail_akonadidatabasetoolplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kmail/mainview)
target_sources(kmail_akonadidatabasetoolplugin PRIVATE
    akonadidatabasetoolsplugin.cpp
    akonadidatabasetoolsplugin.h
)

target_link_libraries(kmail_akonadidatabasetoolplugin
    KF5::PimCommon KF5::PimCommonAkonadi KF${KF_MAJOR_VERSION}::XmlGui KF5::Libkdepim KF${KF_MAJOR_VERSION}::I18n akonadidatasetools
    )

install(TARGETS akonadidatasetools ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

if(BUILD_TESTING)
   add_subdirectory(autotests)
   add_subdirectory(tests)
endif()
