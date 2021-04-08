ecm_qt_declare_logging_category(kaddressbook_importexport_windowscontact_debugfile_autotest_SRCS HEADER importexportwindowscontactplugin_debug.h IDENTIFIER IMPORTEXPORTWINDOWSCONTACTPLUGIN_LOG CATEGORY_NAME org.kde.pim.importexportwindowscontactplugin
    DESCRIPTION "kdepim-addons (Import/Export Windows Contact plugin)"
    EXPORT KDEPIMADDONS
    )
add_definitions(-DWINDOWSCONTACT_DATADIR=\"${CMAKE_CURRENT_SOURCE_DIR}\")
macro(add_windowscontact_unittest _source _additional)
    set( _test ${_source} ${_additional} ${kaddressbook_importexport_windowscontact_debugfile_autotest_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable( ${_name} ${_test})
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(${_name})
    target_link_libraries( ${_name} Qt::Widgets Qt5::Test KF5::I18n KF5::WidgetsAddons Qt5::Xml KF5::Contacts)
endmacro ()
if (NOT WIN32)
add_windowscontact_unittest(importwindowcontacttest.cpp "../importwindowcontact.cpp")
endif()
