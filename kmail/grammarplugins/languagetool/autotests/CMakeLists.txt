# SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_definitions( -DLANGUAGETOOL_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")
macro(add_kmail_languagetool_unittest _source)
    set( _test ${_source} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_grammalecte-${_name})
    target_link_libraries( ${_name} Qt::Test KF5::XmlGui KF5::I18n kmaillanguagetool)
endmacro ()

add_kmail_languagetool_unittest(languagetoolconfigdialogtest.cpp)
add_kmail_languagetool_unittest(languagetoolconfigwidgettest.cpp)
add_kmail_languagetool_unittest(languagetoolgrammarerrortest.cpp)
add_kmail_languagetool_unittest(languagetoolresultwidgettest.cpp)
add_kmail_languagetool_unittest(languagetoolparsertest.cpp)
add_kmail_languagetool_unittest(languagetoolresultjobtest.cpp)
add_kmail_languagetool_unittest(languagetoolcomboboxtest.cpp)
add_kmail_languagetool_unittest(languagetoolgetlistoflanguagejobtest.cpp)
add_kmail_languagetool_unittest(languageinfotest.cpp)
add_kmail_languagetool_unittest(languagetoollistoflanguagesparsertest.cpp)
add_kmail_languagetool_unittest(languagetoolupdatecomboboxtest.cpp)
