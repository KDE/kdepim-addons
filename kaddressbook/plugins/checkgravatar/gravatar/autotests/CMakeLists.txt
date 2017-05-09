set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/../.. )

set(KDEPIMLIBS_RUN_ISOLATED_TESTS TRUE)
set(KDEPIMLIBS_RUN_SQLITE_ISOLATED_TESTS TRUE)
set(kaddressbook_checkgravatarplugin_test_SRCS)
ecm_qt_declare_logging_category(kaddressbook_checkgravatarplugin_test_SRCS HEADER kaddressbook_checkgravatarplugin_debug.h IDENTIFIER KADDRESSBOOK_CHECKGRAVATAR_LOG CATEGORY_NAME org.kde.pim.kaddressbook_checkgravatar)


add_akonadi_isolated_test_advanced( gravatarupdatejobtest.cpp "../job/gravatarupdatejob.cpp;${kaddressbook_checkgravatarplugin_test_SRCS}" "KF5::PimCommon;KF5::Contacts;KF5::Gravatar;KF5::I18n")

add_akonadi_isolated_test_advanced( gravatarupdatedialogtest.cpp "../widgets/gravatarupdatedialog.cpp;../widgets/gravatarupdatewidget.cpp;${kaddressbook_checkgravatarplugin_test_SRCS}" "KF5::PimCommon;KF5::Gravatar;KF5::I18n")
add_akonadi_isolated_test_advanced( gravatarupdatewidgettest.cpp "../widgets/gravatarupdatewidget.cpp;${kaddressbook_checkgravatarplugin_test_SRCS}" "KF5::PimCommon;KF5::Gravatar;KF5::I18n")

#add_akonadi_isolated_test_advanced( checkgravatarplugintest.cpp "../../checkgravatarplugin.cpp;../../checkgravatarplugininterface.cpp" "KF5::PimCommon;KF5::I18n;KF5::XmlGui;KF5::Contacts;KF5::Gravatar;${kaddressbook_checkgravatarplugin_SRCS};${kaddressbook_checkgravatarplugin_test_SRCS}")
