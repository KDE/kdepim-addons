macro(add_foldersettings_plugin_unittest _source )
    set( _test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(foldersettings-${_name})
    target_link_libraries( ${_name} KF5::PimCommon Qt::Test KF5::I18n KF5::MessageViewer folderconfiguresettings)
endmacro ()


add_foldersettings_plugin_unittest(folderconfiguresettingswidgettest.cpp)
