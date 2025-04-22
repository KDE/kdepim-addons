# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_pimautogenerate_unittest _source)
    set(_test ${_source} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name})

    ecm_mark_as_test(pimautogenerate-${_name})
    target_link_libraries(${_name} Qt::Widgets Qt::Test KPim6::AutoGenerateText)
endmacro()


add_pimautogenerate_unittest(autogenerateconfigureaskitemtest.cpp)
add_pimautogenerate_unittest(autogenerateconfigurelistviewtest.cpp)
