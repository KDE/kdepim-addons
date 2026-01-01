# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_foldersettings_plugin_unittest _source)
    set(_test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test})
    add_test(NAME ${_name} COMMAND ${_name})

    ecm_mark_as_test(foldersettings-${_name})
    target_link_libraries(
        ${_name}
        KPim6::PimCommon
        Qt::Test
        KF6::I18n
        KPim6::MessageViewer
        folderconfiguresettings
    )
endmacro()

#add_foldersettings_plugin_unittest(folderconfiguresettingswidgettest.cpp)
