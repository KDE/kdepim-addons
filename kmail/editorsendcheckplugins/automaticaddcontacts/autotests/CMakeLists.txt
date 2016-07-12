set(automaticaddcontacts_common_SRCS)
ecm_qt_declare_logging_category(automaticaddcontacts_common_SRCS HEADER automaticaddcontactsplugin_debug.h IDENTIFIER KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG CATEGORY_NAME log_kmail_automaticaddcontactsplugin)

macro(add_kmail_automaticaddscontacts_unittest _source _additional)
    set( _test ${_source} ${_additional} ${automaticaddcontacts_common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test( ${_name} ${_name} )

    ecm_mark_as_test(kmail_editorplugin-${_name})
    target_link_libraries( ${_name} Qt5::Test KF5::IconThemes KF5::MessageComposer KF5::I18n KF5::PimCommon KF5::AkonadiWidgets)
endmacro ()

add_kmail_automaticaddscontacts_unittest(automaticaddcontactsplugintest.cpp "../automaticaddcontactsjob.cpp;../automaticaddcontactsplugin.cpp;../automaticaddcontactsinterface.cpp;../automaticaddcontactsconfigurewidget.cpp")
add_kmail_automaticaddscontacts_unittest(automaticaddcontactsinterfacetest.cpp "../automaticaddcontactsinterface.cpp")
add_kmail_automaticaddscontacts_unittest(automaticaddcontactswidgettest.cpp "../automaticaddcontactsconfigurewidget.cpp")
add_kmail_automaticaddscontacts_unittest(automaticaddcontactsjobtest.cpp "../automaticaddcontactsjob.cpp")
