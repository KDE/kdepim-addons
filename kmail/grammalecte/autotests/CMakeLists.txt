add_definitions( -DGRAMMALECTE_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")

set(kmail_grammalecteplugin_debug_SRCS)

macro(add_kmail_grammalecte_unittest _source _additional)
    set( _test ${_source} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_grammalecte-${_name})
    target_link_libraries( ${_name} Qt5::Test KF5::XmlGui KF5::IconThemes KF5::I18n libkmailgrammalect)
endmacro ()

add_kmail_grammalecte_unittest(grammalecteparsertest.cpp "")
add_kmail_grammalecte_unittest(grammarresultwidgettest.cpp "")
add_kmail_grammalecte_unittest(grammalectegrammarerrortest.cpp "")
add_kmail_grammalecte_unittest(grammarresultjobtest.cpp "")
add_kmail_grammalecte_unittest(grammarresulttextedittest.cpp "")
