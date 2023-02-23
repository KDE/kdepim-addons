# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

macro(add_plasma_pimeventsplugin_test _source _additional)
    set(_test ${_source}
              ${_additional}
              testdataparser.cpp
              fakepimdatasource.cpp
              ${CMAKE_CURRENT_BINARY_DIR}/../pimeventsplugin_debug.cpp
    )
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name})
    ecm_mark_as_test(plasma-pimeventsplugin-${_name})
    add_definitions(-DPIMEVENT_DATADIR=\"${CMAKE_CURRENT_SOURCE_DIR}\")
    target_link_libraries(${_name} Qt::Core
                                   Qt::Test
                                   KF5::AkonadiCore
                                   KPim${KF_MAJOR_VERSION}::AkonadiCalendar
                                   KF${KF_MAJOR_VERSION}::CalendarCore
                                   KF${KF_MAJOR_VERSION}::CalendarEvents
                                   KPim${KF_MAJOR_VERSION}::EventViews
                                   KF${KF_MAJOR_VERSION}::ConfigCore
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
