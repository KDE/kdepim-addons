# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

set(checkbeforesend_common_SRCS)
ecm_qt_declare_logging_category(checkbeforesend_common_SRCS HEADER checkbeforesendplugin_debug.h IDENTIFIER KMAIL_EDITOR_checkbeforesend_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_checkbeforesendplugin)

macro(add_kmail_checkbeforesend_unittest _source _additional)
    set( _test ${_source} ${_additional} ${checkbeforesend_common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_editorplugin-${_name})
    target_link_libraries( ${_name} Qt::Test KPim${KF_MAJOR_VERSION}::MessageComposer KF${KF_MAJOR_VERSION}::I18n KF5::PimCommon KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::Codecs)
endmacro ()


add_kmail_checkbeforesend_unittest(checkbeforesendplugintest.cpp "../checkbeforesendupdatesmtpdialog.cpp;../configurewidget/checkbeforesendconfiguredialog.cpp;../sendattachments/checkattachmentjob.cpp;../sendattachments/checkattachmentdialog.cpp;../duplicateemails/checkduplicateemailsjob.cpp;../duplicateemails/checkduplicateemailsdialog.cpp;../checkbeforesendplugin.cpp;../checkbeforesendinterface.cpp;../configurewidget/checkbeforesendconfigurewidget.cpp")
add_kmail_checkbeforesend_unittest(checkbeforesendconfigurewidgettest.cpp "../configurewidget/checkbeforesendconfigurewidget.cpp")
add_kmail_checkbeforesend_unittest(checkduplicateemailsdialogtest.cpp "../duplicateemails/checkduplicateemailsdialog.cpp")
add_kmail_checkbeforesend_unittest(checkduplicateemailsjobtest.cpp "../duplicateemails/checkduplicateemailsjob.cpp")

add_kmail_checkbeforesend_unittest(checkattachmentdialogtest.cpp "../sendattachments/checkattachmentdialog.cpp")
add_kmail_checkbeforesend_unittest(checkattachmentjobtest.cpp "../sendattachments/checkattachmentjob.cpp")
add_kmail_checkbeforesend_unittest(checkbeforesendupdatesmtpdialogtest.cpp "../checkbeforesendupdatesmtpdialog.cpp")
