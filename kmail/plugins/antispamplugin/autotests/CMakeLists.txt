# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_kmail_antispamplugin_unittest _source _additional)
    set( _test ${_source} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_antispamplugin-${_name})
    target_link_libraries( ${_name} KF5::PimCommon Qt::Test KF${KF_MAJOR_VERSION}::XmlGui KF${KF_MAJOR_VERSION}::Completion KPim${KF_MAJOR_VERSION}::AkonadiWidgets KPim${KF_MAJOR_VERSION}::MailCommon KPim${KF_MAJOR_VERSION}::Libkdepim KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::GuiAddons)
endmacro ()

add_kmail_antispamplugin_unittest(antispamplugininterfacetest.cpp "../antispamplugininterface.cpp;../../common/antispamwizard.cpp")
