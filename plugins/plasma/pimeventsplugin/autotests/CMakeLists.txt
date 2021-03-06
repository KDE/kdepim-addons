macro(add_plasma_pimeventsplugin_test _source _additional)
    set(_test ${_source}
              ${_additional}
              testdataparser.cpp
              fakepimdatasource.cpp
              ${CMAKE_CURRENT_BINARY_DIR}/../pimeventsplugin_debug.cpp
    )
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test})
    add_test(NAME ${_name} COMMAND ${_name})
    ecm_mark_as_test(plasma-pimeventsplugin-${_name})
    add_definitions(-DPIMEVENT_DATADIR=\"${CMAKE_CURRENT_SOURCE_DIR}\")
    target_link_libraries(${_name} Qt::Core
                                   Qt::Test
                                   KF5::AkonadiCore
                                   KF5::AkonadiCalendar
                                   KF5::CalendarCore
                                   KF5::CalendarEvents
                                   KF5::EventViews
                                   KF5::ConfigCore
    )
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..
                        ${CMAKE_CURRENT_BINARY_DIR}/..
    )
endmacro()
if (NOT WIN32)
    add_plasma_pimeventsplugin_test(eventdatavisitortest.cpp ../eventdatavisitor.cpp)
    add_plasma_pimeventsplugin_test(pimeventsplugintest.cpp "../eventmodel.cpp;../eventdatavisitor.cpp;../pimeventsplugin.cpp;../akonadipimdatasource.cpp;../settingschangenotifier.cpp")
else()
    MESSAGE(STATUS "Need to reactivate autotest on windows here")
endif()
