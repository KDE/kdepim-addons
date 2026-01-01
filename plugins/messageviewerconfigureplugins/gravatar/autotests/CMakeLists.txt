# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_gravatar_plugin_unittest _source _additional)
    set(_test ${_source} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test})
    add_test(NAME ${_name} COMMAND ${_name})

    ecm_mark_as_test(gravatarplugin-${_name})
    target_link_libraries(
        ${_name}
        KPim6::PimCommon
        Qt::Test
        KF6::I18n
        KPim6::Gravatar
        KPim6::MessageViewer
    )
endmacro()

add_gravatar_plugin_unittest(gravatarconfiguresettingspluginwidgettest.cpp "../gravatarconfiguresettingspluginwidget.cpp")
add_gravatar_plugin_unittest(gravatarconfiguresettingsplugindialogtest.cpp "")
