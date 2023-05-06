# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

set(confirmaddressplugin_common_SRCS)
ecm_qt_declare_logging_category(confirmaddressplugin_common_SRCS HEADER confirmaddressplugin_debug.h IDENTIFIER KMAIL_EDITOR_CONFIRMADDRESS_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_confirmaddressplugin)

macro(add_kmail_confirmaddress_unittest _source _additional)
    set( _test ${_source} ${_additional} ${confirmaddressplugin_common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_editorplugin-${_name})
    target_link_libraries( ${_name} Qt::Test KPim6::MessageComposer KF6::I18n KPim6::PimCommon KPim6::Libkdepim KF6::Completion)
endmacro ()

add_kmail_confirmaddress_unittest(confirmaddressplugintest.cpp "../confirmaddressemailentrydialog.cpp;../confirmaddresssimplestringlisteditor.cpp;../confirmaddressconfiguredialog.cpp;../confirmaddressplugin.cpp;../confirmaddressinterface.cpp;../confirmaddressconfigurewidget.cpp;../confirmaddressdialog.cpp;../confirmaddresswidget.cpp;../confirmaddressconfiguretab.cpp;../confirmaddressconfiguretabwidget.cpp;../confirmaddresscheckjob.cpp")


add_kmail_confirmaddress_unittest(confirmaddressconfigurewidgettest.cpp "../confirmaddressemailentrydialog.cpp;../confirmaddresssimplestringlisteditor.cpp;../confirmaddressconfigurewidget.cpp;../confirmaddressconfiguretab.cpp;../confirmaddressconfiguretabwidget.cpp")

add_kmail_confirmaddress_unittest(confirmaddressdialogtest.cpp "../confirmaddressemailentrydialog.cpp;../confirmaddresssimplestringlisteditor.cpp;../confirmaddressdialog.cpp;../confirmaddresswidget.cpp")

add_kmail_confirmaddress_unittest(confirmaddresswidgettest.cpp "../confirmaddressemailentrydialog.cpp;../confirmaddresssimplestringlisteditor.cpp;../confirmaddresswidget.cpp")

add_kmail_confirmaddress_unittest(confirmaddressconfiguretabwidgettest.cpp "../confirmaddressemailentrydialog.cpp;../confirmaddresssimplestringlisteditor.cpp;../confirmaddressconfiguretabwidget.cpp")

add_kmail_confirmaddress_unittest(confirmaddressconfiguretabtest.cpp "../confirmaddressemailentrydialog.cpp;../confirmaddresssimplestringlisteditor.cpp;../confirmaddressconfiguretab.cpp;../confirmaddressconfiguretabwidget.cpp")

add_kmail_confirmaddress_unittest(confirmaddresscheckjobtest.cpp "../confirmaddresscheckjob.cpp")

add_kmail_confirmaddress_unittest(confirmaddressemailentrydialogtest.cpp "../confirmaddressemailentrydialog.cpp")
