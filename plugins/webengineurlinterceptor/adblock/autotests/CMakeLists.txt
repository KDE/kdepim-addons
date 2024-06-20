# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_adblockplugin_unittest _source)
    set(_test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name})

    ecm_mark_as_test(adblockplugin-${_name})
    target_link_libraries(${_name} Qt::Widgets Qt::Test adblockplugin)
endmacro()

add_adblockplugin_unittest(adblockfiltertest.cpp)
add_adblockplugin_unittest(adblockfilterwidgettest.cpp)
add_adblockplugin_unittest(adblockfilterdialogtest.cpp)
add_adblockplugin_unittest(adblockpluginurlinterceptoraddadblocklistwidgettest.cpp)
add_adblockplugin_unittest(adblockfiltertreeviewtest.cpp)
add_adblockplugin_unittest(adblocklistsutiltest.cpp)
add_adblockplugin_unittest(adblockviewfilterwidgettest.cpp)
add_adblockplugin_unittest(adblockviewfilterdialogtest.cpp)
# TODO reactivate it add_adblockplugin_unittest(adblockmanagertest.cpp)
