# SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

set(kmail_markdownplugin_debug_SRCS)
ecm_qt_declare_logging_category(kmail_markdownplugin_debug_SRCS HEADER markdownplugin_debug.h IDENTIFIER KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_markdownplugin)


macro(add_kmail_converttext_unittest _source _additional)
    set( _test ${_source} ${_additional} ${kmail_markdownplugin_debug_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_converttext-${_name})
    target_link_libraries( ${_name} Qt::Test KF5::XmlGui KF5::MessageComposer KF5::I18n Qt::WebEngineWidgets discount::Lib KF5::SyntaxHighlighting kmailmarkdown)
endmacro ()

add_kmail_converttext_unittest(markdowninterfacetest.cpp "../plugin/markdowninterface.cpp")
add_kmail_converttext_unittest(markdownpreviewwidgettest.cpp "")
add_kmail_converttext_unittest(markdownplugintest.cpp "../plugin/markdownplugin.cpp;../plugin/markdowninterface.cpp")
add_kmail_converttext_unittest(markdownconfigurewidgettest.cpp "")
add_kmail_converttext_unittest(markdownconfiguredialogtest.cpp "")
add_kmail_converttext_unittest(markdownpreviewdialogtest.cpp "")
add_kmail_converttext_unittest(markdowncreatelinkwidgettest.cpp "")
add_kmail_converttext_unittest(markdowncreatelinkdialogtest.cpp "")
add_kmail_converttext_unittest(markdowncreateimagedialogtest.cpp "")
add_kmail_converttext_unittest(markdowncreateimagewidgettest.cpp "")
add_kmail_converttext_unittest(markdownutiltest.cpp "")
