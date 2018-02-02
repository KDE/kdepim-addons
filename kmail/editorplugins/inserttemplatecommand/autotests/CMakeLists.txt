macro(add_kmail_editorplugin_unittest _source _additional)
    set( _test ${_source} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_editorplugin-${_name})
    target_link_libraries( ${_name} Qt5::Test KF5::XmlGui KF5::IconThemes KF5::MessageComposer KF5::I18n)
endmacro ()

add_kmail_editorplugin_unittest(inserttemplatecommandplugineditortest.cpp "../inserttemplatecommandplugineditor.cpp;../inserttemplatecommandplugineditorinterface.cpp")

add_kmail_editorplugin_unittest(inserttemplatecommandplugineditorinterfacetest.cpp "../inserttemplatecommandplugineditorinterface.cpp")
