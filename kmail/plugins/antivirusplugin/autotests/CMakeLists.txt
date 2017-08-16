macro(add_kmail_antivirusplugin_unittest _source _additional)
    set( _test ${_source} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_antivirusplugin-${_name})
    target_link_libraries( ${_name} KF5::PimCommon Qt5::Test KF5::XmlGui KF5::Completion KF5::IconThemes KF5::AkonadiWidgets KF5::MailCommon KF5::Libkdepim KF5::I18n)
endmacro ()

add_kmail_antivirusplugin_unittest(antivirusplugininterfacetest.cpp "../antivirusplugininterface.cpp;../../common/antispamwizard.cpp")
