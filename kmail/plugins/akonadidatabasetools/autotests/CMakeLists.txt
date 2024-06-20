# SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_kmail_akonadidatabasetoolsplugin_unittest _source)
    set(_test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name})

    ecm_mark_as_test(kmail_antivirusplugin-${_name})
    target_link_libraries(${_name} KPim6::PimCommon Qt::Test KF6::XmlGui KF6::Completion KPim6::AkonadiWidgets
        KPim6::MailCommon KPim6::Libkdepim KF6::I18n KF6::GuiAddons akonadidatasetools)
endmacro()

add_kmail_akonadidatabasetoolsplugin_unittest(akonadidatabasetoolsplugininterfacetest.cpp)

add_kmail_akonadidatabasetoolsplugin_unittest(akonadidatabasetoolswidgettest.cpp)
