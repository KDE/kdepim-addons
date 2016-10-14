if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()

set(pimeventsplugin_SRCS
    pimeventsplugin.cpp
    akonadipimdatasource.cpp
    eventdatavisitor.cpp
    settingschangenotifier.cpp
    eventmodel.cpp
)

ecm_qt_declare_logging_category(loggingcategory_SRCS
    HEADER pimeventsplugin_debug.h
    IDENTIFIER PIMEVENTSPLUGIN_LOG
    CATEGORY_NAME org.kde.pim.pimeventsplugin
)

set(pimeventsplugins_full_SRCS ${pimeventsplugin_SRCS} ${loggingcategory_SRCS})
kcoreaddons_add_plugin(pimevents JSON pimeventsplugin.json SOURCES
    ${pimeventsplugins_full_SRCS} INSTALL_NAMESPACE plasmacalendarplugins)

target_link_libraries(pimevents
    Qt5::Core
    KF5::AkonadiCore
    KF5::AkonadiCalendar
    KF5::CalendarCore
    KF5::CalendarEvents
    KF5::EventViews # for reading KOrganizer calendar colors
)



######################### NEXT TARGET #######################33

set(plasmapimcalendarsplugin_SRCS
    pimcalendarsplugin.cpp
    pimcalendarsmodel.cpp
    settingschangenotifier.cpp
)

add_library(pimcalendarsplugin SHARED ${plasmapimcalendarsplugin_SRCS} ${loggingcategory_SRCS})
target_link_libraries(pimcalendarsplugin
    Qt5::Core
    Qt5::Qml
    KF5::AkonadiCore
    KF5::CalendarCore
)

install(TARGETS pimcalendarsplugin
        DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/PimCalendars
)
install(FILES qmldir
        DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/plasma/PimCalendars
)
install(FILES PimEventsConfig.qml
        DESTINATION ${PLUGIN_INSTALL_DIR}/plasmacalendarplugins/pimevents
)
