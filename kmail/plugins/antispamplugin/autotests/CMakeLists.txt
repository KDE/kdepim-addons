# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_kmail_antispamplugin_unittest _source _additional)
    set( _test ${_source} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_antispamplugin-${_name})
    target_link_libraries( ${_name} KF5::PimCommon Qt::Test KF5::XmlGui KF5::Completion KF5::AkonadiWidgets KF5::MailCommon KF5::Libkdepim KF5::I18n KF5::GuiAddons)
endmacro ()

add_kmail_antispamplugin_unittest(antispamplugininterfacetest.cpp "../antispamplugininterface.cpp;../../common/antispamwizard.cpp")
