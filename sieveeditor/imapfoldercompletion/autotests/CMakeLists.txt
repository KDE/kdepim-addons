macro(add_sieveeditorplugin_unittest _source _additional)
    set( _test ${_source} ${_additional} ${sieveeditor_plugin_categories_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test})
    add_test( ${_name} ${_name} )

    ecm_mark_as_test(sieveeditorplugin-${_name})
    target_link_libraries( ${_name} Qt5::Widgets Qt5::Test KF5::IMAP KF5::CoreAddons KF5::KIOCore KF5::I18n KF5::Completion)
endmacro ()

add_sieveeditorplugin_unittest(selectimapfolderdialogtest.cpp "../selectimapfolderdialog.cpp;../selectimapfolderwidget.cpp")
add_sieveeditorplugin_unittest(selectimapfolderwidgettest.cpp "../selectimapfolderwidget.cpp")
add_sieveeditorplugin_unittest(selectimapwidgettest.cpp "../selectimapwidget.cpp")
