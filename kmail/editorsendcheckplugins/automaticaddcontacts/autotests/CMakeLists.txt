set(automaticaddcontacts_common_SRCS)
ecm_qt_declare_logging_category(automaticaddcontacts_common_SRCS HEADER automaticaddcontactsplugin_debug.h IDENTIFIER KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG CATEGORY_NAME log_kmail_automaticaddcontactsplugin)

macro(add_kmail_automaticaddscontacts_unittest _source _additional)
    set( _test ${_source} ${_additional} ${automaticaddcontacts_common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test( ${_name} ${_name} )

    ecm_mark_as_test(kmail_editorplugin-${_name})
    target_link_libraries( ${_name} Qt5::Test KF5::IconThemes KF5::MessageComposer KF5::I18n KF5::PimCommon KF5::AkonadiWidgets KF5::Libkdepim)
endmacro ()

set(KDEPIMLIBS_RUN_ISOLATED_TESTS TRUE)
set(KDEPIMLIBS_RUN_SQLITE_ISOLATED_TESTS TRUE)


add_akonadi_isolated_test_advanced(automaticaddcontactsplugintest.cpp "${automaticaddcontacts_common_SRCS};../automaticaddcontactsjob.cpp;../automaticaddcontactsplugin.cpp;../automaticaddcontactsinterface.cpp;../automaticaddcontactsconfigurewidget.cpp" "KF5::IconThemes;KF5::MessageComposer;KF5::I18n;KF5::PimCommon;KF5::AkonadiWidgets;KF5::Contacts;KF5::Libkdepim")
add_akonadi_isolated_test_advanced(automaticaddcontactsinterfacetest.cpp "${automaticaddcontacts_common_SRCS};../automaticaddcontactsjob.cpp;../automaticaddcontactsinterface.cpp" "KF5::IconThemes;KF5::MessageComposer;KF5::I18n;KF5::PimCommon;KF5::AkonadiWidgets;KF5::Contacts;KF5::Libkdepim")
add_akonadi_isolated_test_advanced(automaticaddcontactswidgettest.cpp "${automaticaddcontacts_common_SRCS};../automaticaddcontactsconfigurewidget.cpp" "KF5::IconThemes;KF5::MessageComposer;KF5::I18n;KF5::PimCommon;KF5::AkonadiWidgets;KF5::Contacts;KF5::Libkdepim")
add_kmail_automaticaddscontacts_unittest(automaticaddcontactsjobtest.cpp "../automaticaddcontactsjob.cpp" "KF5::IconThemes;KF5::MessageComposer;KF5::I18n;KF5::PimCommon;KF5::AkonadiWidgets;KF5::Contacts;KF5::Libkdepim")
