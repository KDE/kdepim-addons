# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
# convenience macro to add qtest unit tests
macro(add_kmail_mailmergeunittest _source )
  set(_test ${_source})
  get_filename_component(_name ${_source} NAME_WE)
  add_executable( ${_name} ${_test} ${_name}.h)
  add_test(NAME ${_name} COMMAND ${_name} )
  ecm_mark_as_test(kmail-${_name})
  target_link_libraries( ${_name}
    KPim${KF_MAJOR_VERSION}::PimCommon
    Qt::Test
    KF${KF_MAJOR_VERSION}::KIOCore
    KF${KF_MAJOR_VERSION}::KIOWidgets
    KF${KF_MAJOR_VERSION}::I18n
    mailmerge
  )
endmacro ()

add_kmail_mailmergeunittest( mailmergewidgettest.cpp)
add_kmail_mailmergeunittest(addressbookwidgettest.cpp)
add_kmail_mailmergeunittest(csvwidgettest.cpp)
add_kmail_mailmergeunittest(mailmergedialogtest.cpp)
add_kmail_mailmergeunittest(mailmergejobtest.cpp)
