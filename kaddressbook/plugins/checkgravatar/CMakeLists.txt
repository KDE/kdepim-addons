# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    )
kcoreaddons_add_plugin(kaddressbook_checkgravatarplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/kaddressbook/mainview)

target_sources(kaddressbook_checkgravatarplugin PRIVATE
    gravatar/job/gravatarupdatejob.cpp
    gravatar/widgets/gravatarupdatedialog.cpp
    gravatar/widgets/gravatarupdatewidget.cpp

    checkgravatarplugininterface.cpp
    checkgravatarplugin.cpp
    gravatar/job/gravatarupdatejob.h
    gravatar/widgets/gravatarupdatedialog.h
    gravatar/widgets/gravatarupdatewidget.h

    checkgravatarplugininterface.h
    checkgravatarplugin.h
    )

ecm_qt_declare_logging_category(kaddressbook_checkgravatarplugin HEADER kaddressbook_checkgravatarplugin_debug.h IDENTIFIER KADDRESSBOOK_CHECKGRAVATAR_LOG CATEGORY_NAME org.kde.pim.kaddressbook_checkgravatar
    DESCRIPTION "kdepim-addons (kaddressbook gravatar plugin)"
    EXPORT KDEPIMADDONS
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_checkgravatarplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kaddressbook_checkgravatarplugin
    KPim6::PimCommon KF6::Completion  KPim6::PimCommonAkonadi KF6::XmlGui KPim6::Gravatar KF6::I18n KF6::Contacts
    )

if (BUILD_TESTING)
    add_subdirectory(gravatar/autotests)
    add_subdirectory(gravatar/tests)
endif()
