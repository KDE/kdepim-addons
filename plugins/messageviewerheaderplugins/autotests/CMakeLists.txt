# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
# convenience macro to add qtest unit tests
add_definitions( -DHEADER_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data" )
add_definitions( -DGRANTLEETHEME_DATA_DIR="${CMAKE_SOURCE_DIR}/examples/messageviewergrantleetheme/themes" )

macro(add_messageviewer_header_unittest _source _additional)
    set( _test ${_source} utils.cpp  ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name} )
    
    ecm_mark_as_test(messageviewer-header-${_name})
    set_tests_properties(${_name} PROPERTIES ENVIRONMENT "LC_ALL=C;TZ=UTC")
    target_link_libraries( ${_name} KPim6::MessageViewer KPim6::Libkleo Qt::Test KF6::KIOCore KPim6::Mime KPim6::AkonadiCore KPim6::AkonadiNotes KF6::CalendarCore KPim6::GrantleeTheme KF6::XmlGui KF6::I18n)
endmacro ()


macro(add_messageviewer_header_class_unittest _source )
    set( _test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(messageviewer-header-${_name})
    set_tests_properties(${_name} PROPERTIES ENVIRONMENT "LC_ALL=C;TZ=UTC")
    target_link_libraries( ${_name} KPim6::MessageViewer KPim6::Libkleo Qt::Test KF6::KIOCore KPim6::Mime KPim6::AkonadiCore KPim6::AkonadiNotes KF6::CalendarCore KPim6::GrantleeTheme KF6::XmlGui)
endmacro ()

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/../enterpriseheaderstyleplugin/messageviewer_enterpriseheaderstyleplugin.json.in
        ${CMAKE_CURRENT_BINARY_DIR}/messageviewer_enterpriseheaderstyleplugin.json)


add_messageviewer_header_unittest( briefheaderstyleplugintest.cpp "../briefheaderstyleplugin/briefheaderstrategy.cpp;../briefheaderstyleplugin/briefheaderstyle.cpp;../briefheaderstyleplugin/briefheaderstyleplugin.cpp;../briefheaderstyleplugin/briefheaderstyleinterface.cpp")

add_messageviewer_header_unittest( enterpriseheaderstyleplugintest.cpp "../enterpriseheaderstyleplugin/enterpriseheaderstyle.cpp;../enterpriseheaderstyleplugin/enterpriseheaderstyleplugin.cpp;../enterpriseheaderstyleplugin/enterpriseheaderstyleinterface.cpp")

add_messageviewer_header_unittest( fancyheaderstyleplugintest.cpp "../fancyheaderstyleplugin/fancyheaderstyle.cpp;../fancyheaderstyleplugin/fancyheaderstyleplugin.cpp;../fancyheaderstyleplugin/fancyheaderstyleinterface.cpp")

add_messageviewer_header_unittest( grantleeheaderstyleplugintest.cpp "../grantleeheaderstyleplugin/grantleeheaderstrategy.cpp;../grantleeheaderstyleplugin/grantleeheaderstyleplugin.cpp;../grantleeheaderstyleplugin/grantleeheaderstyleinterface.cpp")

add_messageviewer_header_unittest( longheaderstyleplugintest.cpp "../longheaderstyleplugin/longheaderstyleplugin.cpp;../longheaderstyleplugin/longheaderstyleinterface.cpp")

add_messageviewer_header_unittest( standardsheaderstyleplugintest.cpp "../standardsheaderstyleplugin/standardheaderstrategy.cpp;../standardsheaderstyleplugin/standardsheaderstyleplugin.cpp;../standardsheaderstyleplugin/standardsheaderstyleinterface.cpp")

add_messageviewer_header_class_unittest( headerstylepluginmanagertest.cpp)
