# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_gravatar_plugin_unittest _source _additional)
    set( _test ${_source} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(gravatarplugin-${_name})
    target_link_libraries( ${_name} KF5::PimCommon Qt::Test KF${KF_MAJOR_VERSION}::I18n KF5::Gravatar KF5::MessageViewer)
endmacro ()

add_gravatar_plugin_unittest(gravatarconfiguresettingspluginwidgettest.cpp "../gravatarconfiguresettingspluginwidget.cpp")
add_gravatar_plugin_unittest(gravatarconfiguresettingsplugindialogtest.cpp "")
