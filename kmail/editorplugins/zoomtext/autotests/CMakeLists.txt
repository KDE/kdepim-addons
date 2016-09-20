set(zoomdebug_SRCS)
ecm_qt_declare_logging_category(zoomdebug_SRCS HEADER zoomtexteditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_ZOOMTEXT_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_zoomtexteditorplugin)

macro(add_kmail_editorplugin_unittest _source _additional)
    set( _test ${_source} ${_additional} ${zoomdebug_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test( ${_name} ${_name} )

    ecm_mark_as_test(kmail_editorplugin-${_name})
    target_link_libraries( ${_name} Qt5::Test KF5::XmlGui KF5::IconThemes KF5::MessageComposer KF5::I18n)
endmacro ()

add_kmail_editorplugin_unittest(zoomtextplugineditortest.cpp "../zoomtextplugineditor.cpp;../zoomtextplugineditorinterface.cpp")

add_kmail_editorplugin_unittest(zoomtextplugineditorinterfacetest.cpp "../zoomtextplugineditorinterface.cpp")
