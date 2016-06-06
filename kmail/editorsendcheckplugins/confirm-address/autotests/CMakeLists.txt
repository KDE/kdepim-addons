set(confirmaddressplugin_common_SRCS)
ecm_qt_declare_logging_category(confirmaddressplugin_common_SRCS HEADER confirmaddressplugin_debug.h IDENTIFIER KMAIL_EDITOR_CONFIRMADDRESS_PLUGIN_LOG CATEGORY_NAME log_kmail_confirmaddressplugin)

macro(add_kmail_confirmaddress_unittest _source _additional)
    set( _test ${_source} ${_additional} ${confirmaddressplugin_common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test} )
    add_test( ${_name} ${_name} )

    ecm_mark_as_test(kmail_editorplugin-${_name})
    target_link_libraries( ${_name} Qt5::Test KF5::IconThemes KF5::MessageComposer KF5::I18n)
endmacro ()

add_kmail_confirmaddress_unittest(confirmaddressplugintest.cpp "../confirmaddressplugin.cpp;../confirmaddressinterface.cpp;../confirmaddressconfigurewidget.cpp;../confirmaddressdialog.cpp;../confirmaddresswidget.cpp")

add_kmail_confirmaddress_unittest(confirmaddressinterfacetest.cpp "../confirmaddressinterface.cpp;../confirmaddressconfigurewidget.cpp;../confirmaddressdialog.cpp;../confirmaddresswidget.cpp")

add_kmail_confirmaddress_unittest(confirmaddressconfigurewidgettest.cpp "../confirmaddressconfigurewidget.cpp")

add_kmail_confirmaddress_unittest(confirmaddressdialogtest.cpp "../confirmaddressdialog.cpp;../confirmaddresswidget.cpp")

add_kmail_confirmaddress_unittest(confirmaddresswidgettest.cpp "../confirmaddresswidget.cpp")
