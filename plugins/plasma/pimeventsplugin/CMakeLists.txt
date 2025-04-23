# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

add_definitions(-DTRANSLATION_DOMAIN=\"pimeventsplugin\")
if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
ecm_qt_declare_logging_category(loggingcategory_SRCS
    HEADER pimeventsplugin_debug.h
    IDENTIFIER PIMEVENTSPLUGIN_LOG
    CATEGORY_NAME org.kde.pim.pimeventsplugin
    DESCRIPTION "kdepim-addons (Plasma calendar plugin)"
    OLD_CATEGORY_NAMES log_pimeventsplugin
    EXPORT KDEPIMADDONS
)

kcoreaddons_add_plugin(pimevents INSTALL_NAMESPACE plasmacalendarplugins)
target_sources(
    pimevents
    PRIVATE
        pimeventsplugin.cpp
        akonadipimdatasource.cpp
        eventdatavisitor.cpp
        settingschangenotifier.cpp
        eventmodel.cpp
        ${loggingcategory_SRCS}
        pimeventsplugin.h
        akonadipimdatasource.h
        eventdatavisitor.h
        settingschangenotifier.h
        eventmodel.h
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(pimevents PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(
    pimevents
    Qt::Core
    KPim6::AkonadiCore
    KPim6::AkonadiCalendar
    KF6::CalendarCore
    KF6::CalendarEvents
    KF6::ConfigCore
    KF6::KIOCore
)

######################### NEXT TARGET #######################33

ecm_add_qml_module(pimcalendarsplugin URI org.kde.CalendarEventsPlugin
    QML_FILES
        PimEventsConfig.qml
    SOURCES
        pimcalendarsmodel.cpp
        settingschangenotifier.cpp
        ${loggingcategory_SRCS}
        pimcalendarsmodel.h
        settingschangenotifier.h
    GENERATE_PLUGIN_SOURCE
)

target_link_libraries(pimcalendarsplugin PRIVATE
    Qt::Core
    Qt::Qml
    KPim6::AkonadiCore
    KF6::CalendarCore
    KF6::ConfigCore
)

ecm_finalize_qml_module(pimcalendarsplugin)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(pimcalendarsplugin PROPERTIES UNITY_BUILD ON)
endif()
