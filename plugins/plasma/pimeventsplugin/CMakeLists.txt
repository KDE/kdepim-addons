add_definitions (-DTRANSLATION_DOMAIN=\"pimeventsplugin\")
if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()
kcoreaddons_add_plugin(pimevents JSON pimeventsplugin.json INSTALL_NAMESPACE plasmacalendarplugins)
ecm_qt_declare_logging_category(loggingcategory_SRCS
    HEADER pimeventsplugin_debug.h
    IDENTIFIER PIMEVENTSPLUGIN_LOG
    CATEGORY_NAME org.kde.pim.pimeventsplugin
    DESCRIPTION "kdepim-addons (Plasma calendar plugin)"
    OLD_CATEGORY_NAMES log_pimeventsplugin
    EXPORT KDEPIMADDONS
    )

target_sources(pimevents PRIVATE
    pimeventsplugin.cpp
    akonadipimdatasource.cpp
    eventdatavisitor.cpp
    settingschangenotifier.cpp
    eventmodel.cpp
    ${loggingcategory_SRCS}
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(pimevents PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(pimevents
    Qt::Core
    KF5::AkonadiCore
    KF5::AkonadiCalendar
    KF5::CalendarCore
    KF5::CalendarEvents
    KF5::EventViews # for reading KOrganizer calendar colors
    KF5::ConfigCore
    KF5::KIOCore
    )



######################### NEXT TARGET #######################33

add_library(pimcalendarsplugin SHARED)

target_sources(pimcalendarsplugin PRIVATE
    pimcalendarsplugin.cpp
    pimcalendarsmodel.cpp
    settingschangenotifier.cpp
    ${loggingcategory_SRCS}
    )
target_link_libraries(pimcalendarsplugin
    Qt::Core
    Qt::Qml
    KF5::AkonadiCore
    KF5::CalendarCore
    KF5::ConfigCore
    )
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(pimcalendarsplugin PROPERTIES UNITY_BUILD ON)
endif()
install(TARGETS pimcalendarsplugin
    DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/PimCalendars
    )
install(FILES qmldir
    DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/PimCalendars
    )
install(FILES PimEventsConfig.qml
    DESTINATION ${KDE_INSTALL_PLUGINDIR}/plasmacalendarplugins/pimevents
    )
