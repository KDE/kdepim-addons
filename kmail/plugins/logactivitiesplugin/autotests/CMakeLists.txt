# SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_kmail_logactivitiesplugin_unittest _source _additional)
    set( _test ${_source} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_logactivitiesplugin-${_name})
    target_link_libraries( ${_name} KF5::PimCommon Qt${QT_MAJOR_VERSION}::Test KF5::XmlGui KF5::Completion KF5::PimCommonAkonadi KF5::Libkdepim KF5::I18n)
endmacro ()

add_kmail_logactivitiesplugin_unittest(logactivitiesplugininterfacetest.cpp "../logactivitiesplugininterface.cpp")
