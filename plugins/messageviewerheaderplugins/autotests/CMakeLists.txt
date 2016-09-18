# convenience macro to add qtest unit tests

macro(add_messageviewer_header_unittest _source _additional)
    set( _test ${_source}  ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test( ${_name} ${_name} )
    
    ecm_mark_as_test(messageviewer-header-${_name})
    target_link_libraries( ${_name} KF5::MessageViewer KF5::Libkleo KF5::QGpgme Qt5::Test KF5::KIOCore KF5::Mime KF5::AkonadiCore KF5::AkonadiNotes KF5::CalendarCore KF5::GrantleeTheme)
endmacro ()


macro(add_messageviewer_header_class_unittest _source )
    set( _test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test( ${_name} ${_name} )

    ecm_mark_as_test(messageviewer-header-${_name})
    target_link_libraries( ${_name} KF5::MessageViewer KF5::Libkleo KF5::QGpgme Qt5::Test KF5::KIOCore KF5::Mime KF5::AkonadiCore KF5::AkonadiNotes KF5::CalendarCore KF5::GrantleeTheme)
endmacro ()


add_messageviewer_header_unittest( briefheaderstyleplugintest.cpp "../briefheaderstyleplugin/briefheaderstrategy.cpp;../briefheaderstyleplugin/briefheaderstyle.cpp;../briefheaderstyleplugin/briefheaderstyleplugin.cpp;../briefheaderstyleplugin/briefheaderstyleinterface.cpp")

add_messageviewer_header_unittest( allheaderstyleplugintest.cpp "../allheaderstyleplugin/allheaderstrategy.cpp;../allheaderstyleplugin/allheaderstyleplugin.cpp;../allheaderstyleplugin/allheaderstyleinterface.cpp")

add_messageviewer_header_unittest( enterpriseheaderstyleplugintest.cpp "../enterpriseheaderstyleplugin/enterpriseheaderstyle.cpp;../enterpriseheaderstyleplugin/enterpriseheaderstyleplugin.cpp;../enterpriseheaderstyleplugin/enterpriseheaderstyleinterface.cpp")

add_messageviewer_header_unittest( fancyheaderstyleplugintest.cpp "../fancyheaderstyleplugin/fancyheaderstyle.cpp;../fancyheaderstyleplugin/fancyheaderstyleplugin.cpp;../fancyheaderstyleplugin/fancyheaderstyleinterface.cpp")

add_messageviewer_header_unittest( grantleeheaderstyleplugintest.cpp "../grantleeheaderstyleplugin/grantleeheaderstrategy.cpp;../grantleeheaderstyleplugin/grantleeheaderstyleplugin.cpp;../grantleeheaderstyleplugin/grantleeheaderstyleinterface.cpp")

add_messageviewer_header_unittest( longheaderstyleplugintest.cpp "../longheaderstyleplugin/longheaderstyleplugin.cpp;../longheaderstyleplugin/longheaderstyleinterface.cpp")

add_messageviewer_header_unittest( standardsheaderstyleplugintest.cpp "../standardsheaderstyleplugin/standardheaderstrategy.cpp;../standardsheaderstyleplugin/standardsheaderstyleplugin.cpp;../standardsheaderstyleplugin/standardsheaderstyleinterface.cpp")


add_messageviewer_header_class_unittest( headerstylepluginmanagertest.cpp)
