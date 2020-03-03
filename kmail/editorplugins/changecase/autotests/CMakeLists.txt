set(changecaseplugineditor_common_SRCS)
if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(changecaseplugineditor_common_SRCS HEADER changecaseeditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_CHANGECASE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_changecaseeditorplugin)
else()
    ecm_qt_declare_logging_category(changecaseplugineditor_common_SRCS HEADER changecaseeditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_CHANGECASE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_changecaseeditorplugin
        DESCRIPTION "kdepim-addons (kmail changecase editor plugins)"
        OLD_CATEGORY_NAMES log_kmail_changecaseeditorplugin
        EXPORT KDEPIMADDONS
    )
endif()

macro(add_kmail_editorplugin_unittest _source _additional)
    set( _test ${_source} ${_additional} ${changecaseplugineditor_common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_editorplugin-${_name})
    target_link_libraries( ${_name} Qt5::Test KF5::XmlGui KF5::MessageComposer KF5::I18n)
endmacro ()

add_kmail_editorplugin_unittest(changecaseplugineditortest.cpp "../changecaseplugineditor.cpp;../changecaseplugineditorinterface.cpp")

add_kmail_editorplugin_unittest(changecaseplugineditorinterfacetest.cpp "../changecaseplugineditorinterface.cpp")
