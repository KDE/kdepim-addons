macro(add_kmail_antispamplugin_unittest _source _additional)
    set( _test ${_source} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test( ${_name} ${_name} )

    ecm_mark_as_test(kmail_antispamplugin-${_name})
    target_link_libraries( ${_name} KF5::PimCommon Qt5::Test KF5::XmlGui KF5::Completion KF5::IconThemes KF5::MailCommon)
endmacro ()

add_kmail_antispamplugin_unittest(antispamplugininterfacetest.cpp "../antispamplugininterface.cpp;../../common/antispamwizard.cpp")
