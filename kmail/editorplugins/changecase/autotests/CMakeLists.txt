# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

set(changecaseplugineditor_common_SRCS)
ecm_qt_declare_logging_category(changecaseplugineditor_common_SRCS HEADER changecaseeditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_CHANGECASE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_changecaseeditorplugin)

macro(add_kmail_editorplugin_unittest _source _additional)
    set( _test ${_source} ${_additional} ${changecaseplugineditor_common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_editorplugin-${_name})
    target_link_libraries( ${_name} Qt::Test KF5::XmlGui KF5::MessageComposer KF5::I18n)
endmacro ()

add_kmail_editorplugin_unittest(changecaseplugineditortest.cpp "../changecaseplugineditor.cpp;../changecaseplugineditorinterface.cpp")

add_kmail_editorplugin_unittest(changecaseplugineditorinterfacetest.cpp "../changecaseplugineditorinterface.cpp")
