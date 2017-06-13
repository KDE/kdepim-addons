macro(add_templateparserplugin_unittest _source)
  set(_test ${_source})
  get_filename_component(_name ${_source} NAME_WE)
  add_executable( ${_name} ${_test} )
  ecm_mark_as_test(templateparser-${_name})
  target_link_libraries(${_name}
    KF5::TemplateParser
    Qt5::Test
  )
endmacro()

add_templateparserplugin_unittest(templateparseremailaddressrequesterakonaditest.cpp)
