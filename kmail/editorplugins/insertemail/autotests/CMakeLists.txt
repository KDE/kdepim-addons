# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

macro(add_kmail_editorplugin_unittest _source _additional)
    set(_test ${_source} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name})

    ecm_mark_as_test(kmail_editorplugin-${_name})
    target_link_libraries(${_name} Qt::Test KF6::XmlGui KPim6::MessageComposer KF6::I18n KPim6::AkonadiContactCore)
endmacro()

add_kmail_editorplugin_unittest(insertemailplugineditortest.cpp
    "../insertemailplugineditor.cpp;../insertemailplugineditorinterface.cpp;../selectmaildialog.cpp;../selectmailwidget.cpp")

add_kmail_editorplugin_unittest(insertemailplugineditorinterfacetest.cpp "../insertemailplugineditorinterface.cpp;../selectmaildialog.cpp;../selectmailwidget.cpp")

add_kmail_editorplugin_unittest(selectmaildialogtest.cpp "../selectmaildialog.cpp;../selectmailwidget.cpp")
