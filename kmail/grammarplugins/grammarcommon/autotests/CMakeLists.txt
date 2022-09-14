# SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

macro(add_kmail_grammarcommon_unittest _source)
    set( _test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_grammalecte-${_name})
    target_link_libraries( ${_name} Qt::Test KF5::XmlGui KF5::I18n grammarcommon)
endmacro ()

add_kmail_grammarcommon_unittest(grammarresulttextedittest.cpp)
add_kmail_grammarcommon_unittest(grammarresultutiltest.cpp)
