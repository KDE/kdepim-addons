# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
# convenience macro to add qtest unit tests
macro(add_kmail_mailmergeunittest _source )
  set(_test ${_source} ${_additionalsource})
  get_filename_component(_name ${_source} NAME_WE)
  add_executable( ${_name} ${_test} )
  add_test( ${_name} ${_name} )
  ecm_mark_as_test(kmail-${_name})
  target_link_libraries( ${_name}
    KF5::PimCommon
    Qt::Test
    KF5::KIOCore
    KF5::KIOWidgets
    KF5::I18n
    mailmerge
  )
endmacro ()

add_kmail_mailmergeunittest( mailmergewidgettest.cpp)
add_kmail_mailmergeunittest(addressbookwidgettest.cpp)
add_kmail_mailmergeunittest(csvwidgettest.cpp)
add_kmail_mailmergeunittest(mailmergedialogtest.cpp)
add_kmail_mailmergeunittest(mailmergejobtest.cpp)
