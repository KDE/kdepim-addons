# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_library(kaddressbookmergelibprivate)

target_sources(
    kaddressbookmergelibprivate
    PRIVATE
        job/searchpotentialduplicatecontactjob.cpp
        job/mergecontactsjob.cpp
        job/mergecontacts.cpp
        manualmerge/mergecontactsdialog.cpp
        manualmerge/mergecontactwidget.cpp
        manualmerge/mergecontactwidgetlist.cpp
        searchduplicate/searchandmergecontactduplicatecontactdialog.cpp
        searchduplicate/searchduplicateresultwidget.cpp
        searchduplicate/resultduplicatetreewidget.cpp
        searchduplicate/mergecontactselectinformationtabwidget.cpp
        widgets/mergecontactinfowidget.cpp
        widgets/mergecontactshowresulttabwidget.cpp
        widgets/mergecontactselectinformationwidget.cpp
        widgets/mergecontactselectlistwidget.cpp
        widgets/mergecontactloseinformationwarning.cpp
        widgets/mergecontactselectinformationscrollarea.cpp
        widgets/mergecontacterrorlabel.cpp
        job/searchpotentialduplicatecontactjob.h
        job/mergecontactsjob.h
        job/mergecontacts.h
        manualmerge/mergecontactsdialog.h
        manualmerge/mergecontactwidget.h
        manualmerge/mergecontactwidgetlist.h
        searchduplicate/searchandmergecontactduplicatecontactdialog.h
        searchduplicate/searchduplicateresultwidget.h
        searchduplicate/resultduplicatetreewidget.h
        searchduplicate/mergecontactselectinformationtabwidget.h
        widgets/mergecontactinfowidget.h
        widgets/mergecontactshowresulttabwidget.h
        widgets/mergecontactselectinformationwidget.h
        widgets/mergecontactselectlistwidget.h
        widgets/mergecontactloseinformationwarning.h
        widgets/mergecontactselectinformationscrollarea.h
        widgets/mergecontacterrorlabel.h
)
ecm_qt_declare_logging_category(kaddressbookmergelibprivate HEADER kaddressbookmergelibprivate_debug.h IDENTIFIER KADDRESSBOOKMERGELIBPRIVATE_LOG CATEGORY_NAME org.kde.pim.kaddressbookmergelibprivate
    DESCRIPTION "kdepim-addons (kaddressbook merge contact plugin)"
    EXPORT KDEPIMADDONS
)

generate_export_header(
    kaddressbookmergelibprivate
    BASE_NAME kaddressbookmergelib
)
if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kaddressbookmergelibprivate PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(
    kaddressbookmergelibprivate
    PRIVATE
        Qt::Network
        KF6::I18n
        KF6::Contacts
        KPim6::AkonadiContactWidgets
        KF6::ConfigCore
        KF6::WidgetsAddons
        KPim6::AkonadiWidgets
        KF6::ItemViews
        KF6::ConfigGui
)

set_target_properties(
    kaddressbookmergelibprivate
    PROPERTIES
        VERSION ${KDEPIMADDONS_LIB_VERSION}
        SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
)

install(
    TARGETS kaddressbookmergelibprivate ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY NAMELINK_SKIP
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
