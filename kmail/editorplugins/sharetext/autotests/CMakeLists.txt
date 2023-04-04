# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

set(sharetextplugineditor_common_SRCS)
ecm_qt_declare_logging_category(sharetextplugineditor_common_SRCS HEADER sharetexteditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_SHARETEXT_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_sharetexteditorplugin)

macro(add_kmail_editorplugin_unittest _source _additional)
    set( _test ${_source} ${_additional} ${sharetextplugineditor_common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_editorplugin-${_name})
    target_link_libraries( ${_name} Qt::Test KF6::XmlGui KPim6::MessageComposer KF6::I18n KPim6::PimTextEdit)
endmacro ()

add_kmail_editorplugin_unittest(sharetextplugineditortest.cpp "../sharetextplugineditor.cpp;../sharetextplugineditorinterface.cpp;../sharetextpurposemenuwidget.cpp")

add_kmail_editorplugin_unittest(sharetextplugineditorinterfacetest.cpp "../sharetextplugineditorinterface.cpp;../sharetextpurposemenuwidget.cpp")
