# SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

macro(add_kmail_externalcomposer_unittest _source _additional)
    set(_test ${_source} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name})

    ecm_mark_as_test(kmail_editorinitplugin-${_name})
    target_link_libraries(
        ${_name}
        Qt::Test
        KPim6::MessageComposer
        KF6::I18n
        KPim6::PimCommon
        KF6::KIOWidgets
    )
endmacro()

add_kmail_externalcomposer_unittest(externalcomposerconfigurewidgettest.cpp "../externalcomposerconfigurewidget.cpp")
add_kmail_externalcomposer_unittest(externalcomposerconfiguredialogtest.cpp "../externalcomposerconfiguredialog.cpp;../externalcomposerconfigurewidget.cpp")
add_kmail_externalcomposer_unittest(externalcomposerplugineditortest.cpp "../externalcomposerplugineditor.cpp;../externalcomposerplugineditorinterface.cpp;../externalcomposerconfiguredialog.cpp;../externalcomposerconfigurewidget.cpp")
