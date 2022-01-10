# SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_templateparserplugin_unittest _source _extrasources)
  set(_test ${_source} ${_extrasources})
  get_filename_component(_name ${_source} NAME_WE)
  add_executable( ${_name} ${_test} )
  add_test(NAME ${_name} COMMAND ${_name})
  ecm_mark_as_test(templateparserplugin-${_name})
  target_link_libraries(${_name}
    KF5::TemplateParser
    KF5::AkonadiContact
    Qt${QT_MAJOR_VERSION}::Test
    KF5::Service
  )
endmacro()

add_templateparserplugin_unittest(templateparseremailaddressrequesterakonaditest.cpp "../templateparseremailaddressrequesterakonadi.cpp")
