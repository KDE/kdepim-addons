add_definitions (-DTEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/externaldatas")
ecm_qt_declare_logging_category(common_SRCS HEADER externalscriptplugin_debug.h IDENTIFIER EXTERNALSCRIPTPLUGIN_LOG CATEGORY_NAME org.kde.pim.externalscriptplugin)

macro(add_messageviewer_viewerplugin_external_plugin_unittest _source _additional _jsonfile)
    set( _test ${_source}  ${_additional} ${common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    if (${_jsonfile})
       kcoreaddons_desktop_to_json(${_name} ${_jsonfile})
    endif()
    ecm_add_test(${_test}
                 TEST_NAME ${_name}
                 NAME_PREFIX "messageviewerplugins-"
                 LINK_LIBRARIES KF5::MessageViewer KF5::Libkleo KF5::QGpgme Qt5::Test KF5::KIOCore KF5::Mime KF5::AkonadiCore KF5::AkonadiNotes KF5::CalendarCore KF5::GrantleeTheme KF5::IncidenceEditor
                )
endmacro ()


add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternalscriptinfotest.cpp "../viewerpluginexternalscriptparseargument.cpp;../viewerpluginexternalscriptinfo.cpp;../viewerpluginexternalscriptsloadjob.cpp" "")
add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternalscriptsloadjobtest.cpp "../viewerpluginexternalscriptsloadjob.cpp;../viewerpluginexternalscriptinfo.cpp" "")
add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternalscriptparseargumenttest.cpp "../viewerpluginexternalscriptparseargument.cpp" "")
