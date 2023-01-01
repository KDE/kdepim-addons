# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

macro(add_kmail_editorpluginquicktext_unittest _source)
    set( _test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_editorpluginquicktext-${_name})
    target_link_libraries( ${_name} Qt::Test KF5::XmlGui KF5::MessageComposer KF5::I18n KF5::PimTextEdit kmailquicktextpluginprivate KF5::MailCommon)
endmacro ()

add_kmail_editorpluginquicktext_unittest(quicktextmenutest.cpp)
add_kmail_editorpluginquicktext_unittest(quicktextconfiguredialogtest.cpp)
add_kmail_editorpluginquicktext_unittest(quicktextconfigurewidgettest.cpp)
add_kmail_editorpluginquicktext_unittest(quicktextwidgettest.cpp)
