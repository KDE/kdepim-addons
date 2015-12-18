set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/../.. )

set(KDEPIMLIBS_RUN_ISOLATED_TESTS TRUE)
set(KDEPIMLIBS_RUN_SQLITE_ISOLATED_TESTS TRUE)

add_akonadi_isolated_test_advanced( gravatarupdatejobtest.cpp "../job/gravatarupdatejob.cpp" "KF5::PimCommon;KF5::Contacts;KF5::Gravatar")

add_akonadi_isolated_test_advanced( gravatarupdatedialogtest.cpp "../widgets/gravatarupdatedialog.cpp;../widgets/gravatarupdatewidget.cpp" "KF5::PimCommon;KF5::Gravatar")
add_akonadi_isolated_test_advanced( gravatarupdatewidgettest.cpp "../widgets/gravatarupdatewidget.cpp" "KF5::PimCommon;KF5::Gravatar")
