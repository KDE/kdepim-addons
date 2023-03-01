# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_kmail_editorplugin_unittest _source _additional)
    set( _test ${_source} ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_editorplugin-${_name})
    target_link_libraries( ${_name} Qt::Test KF${KF_MAJOR_VERSION}::XmlGui KPim${KF_MAJOR_VERSION}::MessageComposer KF${KF_MAJOR_VERSION}::I18n)
endmacro ()

add_kmail_editorplugin_unittest(insertspecialcharacterplugineditortest.cpp "../insertspecialcharacterplugineditor.cpp;../insertspecialcharacterplugineditorinterface.cpp")

add_kmail_editorplugin_unittest(insertspecialcharacterplugineditorinterfacetest.cpp "../insertspecialcharacterplugineditorinterface.cpp")
