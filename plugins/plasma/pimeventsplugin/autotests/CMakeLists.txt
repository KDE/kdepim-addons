macro(add_plasma_pimeventsplugin_test _source _additional)
    set(_test ${_source} ${_additional} testdataparser.cpp)
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test})
    add_test(${_name} ${_name})
    ecm_mark_as_test(plasma-pimeventsplugin-${_name})
    add_definitions(-DQT_TESTCASE_BUILDDIR=\"${CMAKE_CURRENT_SOURCE_DIR}\")
    target_link_libraries(${_name} Qt5::Core Qt5::Test KF5::AkonadiCore KF5::AkonadiCalendar KF5::CalendarCore KF5::CalendarEvents)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..
                        ${CMAKE_CURRENT_BINARY_DIR}/..)
endmacro()

add_plasma_pimeventsplugin_test(eventdatavisitortest.cpp ../eventdatavisitor.cpp)
#add_plasma_pimeventsplugin_test(pimeventsplugintest.cpp "../eventdatavisitor.cpp;../pimeventsplugin.cpp")
