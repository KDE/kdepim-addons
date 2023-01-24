# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

set(kmail_insertshorturleditorplugin_autotest_SRCS)

ecm_qt_declare_logging_category(kmail_insertshorturleditorplugin_autotest_SRCS HEADER kmail_insertshorturl_debug.h IDENTIFIER KMAIL_INSERTSHORTURL_LOG CATEGORY_NAME org.kde.pim.kmail_insertshorturl)
macro(add_kmail_editorplugin_unittest _source _additional)
    set( _test ${_source} ${_additional} ${kmail_insertshorturleditorplugin_autotest_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_editorplugin-${_name})
    target_link_libraries( ${_name} Qt::Test KF${KF_MAJOR_VERSION}::XmlGui KF5::MessageComposer KF${KF_MAJOR_VERSION}::I18n shorturlpluginprivate)
endmacro ()


add_kmail_editorplugin_unittest(insertshorturlplugineditortest.cpp
    "../insertshorturlplugineditor.cpp;../insertshorturlplugineditorinterface.cpp;../insertshorturlconfiguredialog.cpp;../insertshorturlconfigurewidget.cpp")

add_kmail_editorplugin_unittest(insertshorturlplugineditorinterfacetest.cpp "../insertshorturlplugineditorinterface.cpp;../insertshorturlconfiguredialog.cpp;../insertshorturlconfigurewidget.cpp")
add_kmail_editorplugin_unittest(insertshorturlconfigurewidgettest.cpp "../insertshorturlconfigurewidget.cpp")
add_kmail_editorplugin_unittest(insertshorturlconfiguredialogtest.cpp "../insertshorturlconfiguredialog.cpp;../insertshorturlconfigurewidget.cpp")
