add_definitions (-DTRANSLATION_DOMAIN=\"pimeventsplugin\")
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
if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(loggingcategory_SRCS
        HEADER pimeventsplugin_debug.h
        IDENTIFIER PIMEVENTSPLUGIN_LOG
        CATEGORY_NAME org.kde.pim.pimeventsplugin
    )
else()
    ecm_qt_declare_logging_category(loggingcategory_SRCS
        HEADER pimeventsplugin_debug.h
        IDENTIFIER PIMEVENTSPLUGIN_LOG
        CATEGORY_NAME org.kde.pim.pimeventsplugin
        DESCRIPTION "kdepim-addons (Plasma calendar plugin)"
        OLD_CATEGORY_NAMES log_pimeventsplugin
        EXPORT KDEPIMADDONS
        )
endif()


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
    KF5::ConfigCore
    KF5::KIOCore
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
    KF5::ConfigCore
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
