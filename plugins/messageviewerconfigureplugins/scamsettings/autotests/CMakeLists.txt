# SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_scamconfigure_plugin_unittest _source)
    set( _test ${_source} )
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(scamplugin-${_name})
    target_link_libraries( ${_name} Qt::Test KF${KF_MAJOR_VERSION}::I18n KF5::MessageViewer scamconfiguresettings)
endmacro ()

add_scamconfigure_plugin_unittest(scamconfiguresettingswidgettest.cpp)
add_scamconfigure_plugin_unittest(scamconfiguresettingsdialogtest.cpp)
