add_definitions (-DTEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/externaldatas")

ecm_qt_declare_logging_category(common_SRCS HEADER externalscriptplugin_debug.h IDENTIFIER EXTERNALSCRIPTPLUGIN_LOG CATEGORY_NAME org.kde.pim.externalscriptplugin)

macro(add_messageviewer_viewerplugin_external_plugin_unittest _source _additional _jsonfile)
    set( _test ${_source}  ${_additional} ${common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    if (${_jsonfile})
       kcoreaddons_desktop_to_json(${_name} ${_jsonfile})
    endif()
    ecm_add_test(${_test}
                 TEST_NAME ${_name}
                 NAME_PREFIX "messageviewerplugins-"
                 LINK_LIBRARIES KF5::MessageViewer Qt::Test KF5::KIOCore KF5::Mime KF5::AkonadiCore KF5::I18n KF5::XmlGui KF5::PimCommon KF5::KIOWidgets KF5::Libkdepim
                )
endmacro ()


add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternalscriptinfotest.cpp "../viewerpluginexternalscriptparseargument.cpp;../viewerpluginexternalscriptinfo.cpp;../viewerpluginexternalscriptsloadjob.cpp" "")
add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternalscriptsloadjobtest.cpp "../viewerpluginexternalscriptsloadjob.cpp;../viewerpluginexternalscriptinfo.cpp" "")
add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternalscriptparseargumenttest.cpp "../viewerpluginexternalscriptparseargument.cpp" "")
add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternalconfigurewidgettest.cpp "../configuredialog/viewerpluginexternaleditwidget.cpp;../configuredialog/viewerpluginexternaleditdialog.cpp;../configuredialog/viewerpluginexternalconfigurewidget.cpp;../viewerpluginexternalscriptsloadjob.cpp;../viewerpluginexternalscriptinfo.cpp" "")
add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternalconfiguredialogtest.cpp "../configuredialog/viewerpluginexternaleditwidget.cpp;../configuredialog/viewerpluginexternaleditdialog.cpp;../configuredialog/viewerpluginexternalconfiguredialog.cpp;../configuredialog/viewerpluginexternalconfigurewidget.cpp;../viewerpluginexternalscriptsloadjob.cpp;../viewerpluginexternalscriptinfo.cpp" "")
add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternaleditwidgettest.cpp "../viewerpluginexternalscriptinfo.cpp;../configuredialog/viewerpluginexternaleditwidget.cpp" "")
add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternaleditdialogtest.cpp "../viewerpluginexternalscriptinfo.cpp;../configuredialog/viewerpluginexternaleditdialog.cpp;../configuredialog/viewerpluginexternaleditwidget.cpp" "")
#add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternalscripttest.cpp "../viewerpluginexternalscriptparseargument.cpp;../viewerpluginexternalscript.cpp;../viewerpluginexternalscriptinterface.cpp;../viewerpluginexternalscriptinfo.cpp;../configuredialog/viewerpluginexternaleditdialog.cpp;../configuredialog/viewerpluginexternaleditwidget.cpp;../configuredialog/viewerpluginexternaleditwidget.cpp;../configuredialog/viewerpluginexternaleditdialog.cpp;../configuredialog/viewerpluginexternalconfigurewidget.cpp;../viewerpluginexternalscriptsloadjob.cpp;../viewerpluginexternalscriptinfo.cpp" "")
