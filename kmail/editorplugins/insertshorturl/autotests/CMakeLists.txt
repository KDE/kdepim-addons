set(kmail_insertshorturleditorplugin_autotest_SRCS)

if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(kmail_insertshorturleditorplugin_autotest_SRCS HEADER kmail_insertshorturl_debug.h IDENTIFIER KMAIL_INSERTSHORTURL_LOG CATEGORY_NAME org.kde.pim.kmail_insertshorturl)
else()
    ecm_qt_declare_logging_category(kmail_insertshorturleditorplugin_autotest_SRCS HEADER kmail_insertshorturl_debug.h IDENTIFIER KMAIL_INSERTSHORTURL_LOG CATEGORY_NAME org.kde.pim.kmail_insertshorturl
        DESCRIPTION "kdepim-addons (kmail insert short url plugin)"
        EXPORT KDEPIMADDONS
    )
endif()
macro(add_kmail_editorplugin_unittest _source _additional)
    set( _test ${_source} ${_additional} ${kmail_insertshorturleditorplugin_autotest_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(kmail_editorplugin-${_name})
    target_link_libraries( ${_name} Qt5::Test KF5::XmlGui KF5::MessageComposer KF5::I18n shorturlpluginprivate)
endmacro ()


add_kmail_editorplugin_unittest(insertshorturlplugineditortest.cpp
    "../insertshorturlplugineditor.cpp;../insertshorturlplugineditorinterface.cpp;../insertshorturlconfiguredialog.cpp;../insertshorturlconfigurewidget.cpp")

add_kmail_editorplugin_unittest(insertshorturlplugineditorinterfacetest.cpp "../insertshorturlplugineditorinterface.cpp;../insertshorturlconfiguredialog.cpp;../insertshorturlconfigurewidget.cpp")
add_kmail_editorplugin_unittest(insertshorturlconfigurewidgettest.cpp "../insertshorturlconfigurewidget.cpp")
add_kmail_editorplugin_unittest(insertshorturlconfiguredialogtest.cpp "../insertshorturlconfiguredialog.cpp;../insertshorturlconfigurewidget.cpp")
