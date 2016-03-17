set(pimeventsplugin_SRCS
    pimeventsplugin.cpp
    eventdatavisitor.cpp
)

ecm_qt_declare_logging_category(pimeventsplugin_SRCS
    HEADER pimeventsplugin_debug.h
    IDENTIFIER PIMEVENTSPLUGIN_LOG
    CATEGORY_NAME log_pimeventsplugin
)



add_library(pimevents MODULE ${pimeventsplugin_SRCS})
target_link_libraries(pimevents
    Qt5::Core
    KF5::AkonadiCore
    KF5::AkonadiCalendar
    KF5::CalendarCore
    KF5::CalendarEvents
)

install(TARGETS pimevents
        DESTINATION ${PLUGIN_INSTALL_DIR}/plasmacalendarplugins
)
install(FILES PimEventsConfig.qml
        DESTINATION ${PLUGIN_INSTALL_DIR}/plasmacalendarplugins/pimevents
)
