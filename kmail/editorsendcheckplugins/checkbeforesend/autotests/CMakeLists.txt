set(checkbeforesend_common_SRCS)
ecm_qt_declare_logging_category(checkbeforesend_common_SRCS HEADER checkbeforesend_debug.h IDENTIFIER KMAIL_EDITOR_CHECKBEFORESEND_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_checkbeforesend)

macro(add_kmail_checkbeforesend_unittest _source _additional)
    set( _test ${_source} ${_additional} ${checkbeforesend_common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test( ${_name} ${_name} )

    ecm_mark_as_test(kmail_editorplugin-${_name})
    target_link_libraries( ${_name} Qt5::Test KF5::IconThemes KF5::MessageComposer KF5::I18n KF5::PimCommon)
endmacro ()


add_kmail_checkbeforesend_unittest(checkbeforesendplugintest.cpp "../sendattachments/checkattachmentjob.cpp;../sendattachments/checkattachmentdialog.cpp;../duplicateemails/checkduplicateemailsjob.cpp;../duplicateemails/checkduplicateemailsdialog.cpp;../checkbeforesendplugin.cpp;../checkbeforesendinterface.cpp;../configurewidget/checkbeforesendconfigurewidget.cpp")
add_kmail_checkbeforesend_unittest(checkbeforesendconfigurewidgettest.cpp "../configurewidget/checkbeforesendconfigurewidget.cpp")
add_kmail_checkbeforesend_unittest(checkduplicateemailsdialogtest.cpp "../duplicateemails/checkduplicateemailsdialog.cpp")
add_kmail_checkbeforesend_unittest(checkduplicateemailsjobtest.cpp "../duplicateemails/checkduplicateemailsjob.cpp")

add_kmail_checkbeforesend_unittest(checkattachmentdialogtest.cpp "../sendattachments/checkattachmentdialog.cpp")
add_kmail_checkbeforesend_unittest(checkattachmentjobtest.cpp "../sendattachments/checkattachmentjob.cpp")
