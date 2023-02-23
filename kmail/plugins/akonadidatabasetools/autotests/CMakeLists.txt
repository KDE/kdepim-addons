# SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_kmail_akonadidatabasetoolsplugin_unittest _source)
    set( _test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_antivirusplugin-${_name})
    target_link_libraries( ${_name} KF5::PimCommon Qt::Test KF${KF_MAJOR_VERSION}::XmlGui KF${KF_MAJOR_VERSION}::Completion KF5::AkonadiWidgets
        KPim${KF_MAJOR_VERSION}::MailCommon KPim${KF_MAJOR_VERSION}::Libkdepim KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::GuiAddons akonadidatasetools)
endmacro ()

add_kmail_akonadidatabasetoolsplugin_unittest(akonadidatabasetoolsplugininterfacetest.cpp)

add_kmail_akonadidatabasetoolsplugin_unittest(akonadidatabasetoolswidgettest.cpp)
