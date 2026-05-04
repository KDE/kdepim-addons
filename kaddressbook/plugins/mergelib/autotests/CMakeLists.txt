# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

set(kaddressbookmergelibprivate_common_SRCS)
ecm_qt_declare_logging_category(kaddressbookmergelibprivate_common_SRCS HEADER kaddressbookmergelibprivate_debug.h IDENTIFIER KADDRESSBOOKMERGELIBPRIVATE_LOG CATEGORY_NAME org.kde.pim.kaddressbookmergelibprivate)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
include_directories(${CMAKE_BINARY_DIR}/kaddressbook/)

# Convenience macro to add unit tests.
macro(kaddressbook_merge _source _additional _additionallib)
    set(_test ${_source} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name})
    ecm_mark_as_test(kaddressbookmerge-${_name})
    target_link_libraries(
        ${_name}
        kaddressbookmergelibprivate
        Qt::Test
        KPim6::AkonadiCore
        KF6::Contacts
        KF6::I18n
        ${_additionallib}
    )
endmacro()

kaddressbook_merge(mergecontactstest.cpp "../job/mergecontacts.cpp;../kaddressbookmergelibprivate_debug.cpp" "")

if(KDEPIM_RUN_AKONADI_TEST)
    set(KDEPIMLIBS_RUN_ISOLATED_TESTS TRUE)
    set(KDEPIMLIBS_RUN_SQLITE_ISOLATED_TESTS TRUE)

    add_akonadi_isolated_test(SOURCE mergecontactinfowidgettest.cpp
        ADDITIONAL_SOURCES
            ../widgets/mergecontactinfowidget.cpp
            ${kaddressbookmergelibprivate_common_SRCS}
        LINK_LIBRARIES
            KPim6::AkonadiContactWidgets
    )
    add_akonadi_isolated_test(SOURCE mergecontactwidgettest.cpp
        ADDITIONAL_SOURCES
            ../widgets/mergecontactinfowidget.cpp
            ${kaddressbookmergelibprivate_common_SRCS}
        LINK_LIBRARIES
            kaddressbookmergelibprivate
            KF6::Contacts
            KPim6::AkonadiContactWidgets
            KF6::WidgetsAddons
    )
    add_akonadi_isolated_test(SOURCE searchandmergecontactduplicatecontactdialogtest.cpp
        ADDITIONAL_SOURCES
            ${kaddressbookmergelibprivate_common_SRCS}
        LINK_LIBRARIES
            kaddressbookmergelibprivate
            KF6::Contacts
            Qt6::Widgets
    )
    add_akonadi_isolated_test(SOURCE searchduplicateresultwidgettest.cpp
        ADDITIONAL_SOURCES
            ${kaddressbookmergelibprivate_common_SRCS}
        LINK_LIBRARIES
            kaddressbookmergelibprivate
            KF6::Contacts
            KF6::WidgetsAddons
            KPim6::AkonadiWidgets
            KPim6::AkonadiContactWidgets
    )
    add_akonadi_isolated_test(SOURCE resultduplicatetreewidgettest.cpp
        ADDITIONAL_SOURCES
            ${kaddressbookmergelibprivate_common_SRCS}
        LINK_LIBRARIES
            kaddressbookmergelibprivate
            KF6::Contacts
            Qt6::Widgets
    )
    add_akonadi_isolated_test(SOURCE searchpotentialduplicatecontactjobtest.cpp
        ADDITIONAL_SOURCES
            ${kaddressbookmergelibprivate_common_SRCS}
            ../job/searchpotentialduplicatecontactjob.cpp
        LINK_LIBRARIES
            KF6::Contacts
    )
    add_akonadi_isolated_test(SOURCE mergecontactselectinformationwidgettest.cpp
        ADDITIONAL_SOURCES
            ${kaddressbookmergelibprivate_common_SRCS}
        LINK_LIBRARIES
            kaddressbookmergelibprivate
            KF6::Contacts
            Qt6::Widgets
    )
    add_akonadi_isolated_test(SOURCE mergecontactselectlistwidgettest.cpp
        ADDITIONAL_SOURCES
            ${kaddressbookmergelibprivate_common_SRCS}
        LINK_LIBRARIES
            kaddressbookmergelibprivate
            KF6::Contacts
            Qt6::Widgets
    )

    add_akonadi_isolated_test(SOURCE mergecontactselectinformationscrollareatest.cpp
        ADDITIONAL_SOURCES
            ${kaddressbookmergelibprivate_common_SRCS}
            ../widgets/mergecontactinfowidget.cpp
        LINK_LIBRARIES
            kaddressbookmergelibprivate
            KF6::Contacts
            KPim6::AkonadiContactWidgets
    )

    add_akonadi_isolated_test(SOURCE mergecontactselectinformationtabwidgettest.cpp
        ADDITIONAL_SOURCES
            ${kaddressbookmergelibprivate_common_SRCS}
        LINK_LIBRARIES
            kaddressbookmergelibprivate
            KF6::Contacts
            Qt6::Widgets
    )

    add_akonadi_isolated_test(SOURCE mergecontactsdialogtest.cpp
        ADDITIONAL_SOURCES
            ${kaddressbookmergelibprivate_common_SRCS}
            ../widgets/mergecontacterrorlabel.cpp
            ../widgets/mergecontactinfowidget.cpp
        LINK_LIBRARIES
            kaddressbookmergelibprivate
            KF6::Contacts
            KPim6::AkonadiContactWidgets
            KF6::I18n
            KF6::WidgetsAddons
    )
    add_akonadi_isolated_test(SOURCE mergecontactwidgetlisttest.cpp
        ADDITIONAL_SOURCES
            ${kaddressbookmergelibprivate_common_SRCS}
            ../manualmerge/mergecontactwidgetlist.cpp;
        LINK_LIBRARIES
            kaddressbookmergelibprivate
            KF6::Contacts
            KPim6::AkonadiContactWidgets
            KF6::I18n
    )
endif()

set(kaddressbook_merge_mergecontactloseinformationwarning_source
    mergecontactloseinformationwarningtest.cpp
    ${kaddressbookmergelibprivate_common_SRCS}
)
add_executable(
    mergecontactloseinformationwarningtest
    ${kaddressbook_merge_mergecontactloseinformationwarning_source}
)
add_test(
    NAME mergecontactloseinformationwarningtest
    COMMAND mergecontactloseinformationwarningtest
)
ecm_mark_as_test(mergecontactloseinformationwarningtest)
target_link_libraries(
    mergecontactloseinformationwarningtest
    Qt::Test
    Qt::Gui
    kaddressbookmergelibprivate
    KF6::WidgetsAddons
    KF6::I18n
)
