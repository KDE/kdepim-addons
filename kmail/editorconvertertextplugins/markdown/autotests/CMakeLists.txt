set(kmail_markdownplugin_debug_SRCS)
ecm_qt_declare_logging_category(kmail_markdownplugin_debug_SRCS HEADER markdownplugin_debug.h IDENTIFIER KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_markdownplugin)

macro(add_kmail_converttext_unittest _source _additional)
    set( _test ${_source} ${_additional} ${kmail_markdownplugin_debug_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_converttext-${_name})
    target_link_libraries( ${_name} Qt5::Test KF5::XmlGui KF5::IconThemes KF5::MessageComposer KF5::I18n Qt5::WebEngineWidgets discount::Lib)
endmacro ()

add_kmail_converttext_unittest(markdowninterfacetest.cpp "../markdowninterface.cpp")
add_kmail_converttext_unittest(markdownpreviewwidgettest.cpp "../markdownpreviewwidget.cpp;../markdowndocument.cpp;../markdownpreviewpage.cpp")
add_kmail_converttext_unittest(markdownplugintest.cpp "../markdownplugin.cpp;../markdowninterface.cpp;../markdowndocument.cpp;../markdownpreviewpage.cpp;../markdownconfiguredialog.cpp;../markdownconfigurewidget.cpp")
add_kmail_converttext_unittest(markdowndocumenttest.cpp "../markdowndocument.cpp")
add_kmail_converttext_unittest(markdownconfigurewidgettest.cpp "../markdownconfigurewidget.cpp")
add_kmail_converttext_unittest(markdownconfiguredialogtest.cpp "../markdownconfiguredialog.cpp;../markdownconfigurewidget.cpp")
