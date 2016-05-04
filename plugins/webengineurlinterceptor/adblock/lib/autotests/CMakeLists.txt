set(messageviewer_adblock_test_common_SRCS)
ecm_qt_declare_logging_category(messageviewer_adblock_test_common_SRCS HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME log_adblockinterceptor)


set( adblockpluginurlinterceptorconfigurewidgettest_SRCS ${messageviewer_adblock_test_common_SRCS} adblockpluginurlinterceptorconfigurewidgettest.cpp  ../widgets/adblockpluginurlinterceptorconfigurewidget.cpp)
add_executable( adblockpluginurlinterceptorconfigurewidgettest ${adblockpluginurlinterceptorconfigurewidgettest_SRCS})
add_test(adblockpluginurlinterceptorconfigurewidgettest adblockpluginurlinterceptorconfigurewidgettest)
ecm_mark_as_test(adblockpluginurlinterceptorconfigurewidgettest)
target_link_libraries( adblockpluginurlinterceptorconfigurewidgettest adblocklibprivate Qt5::Test Qt5::Widgets KF5::MessageViewer
    KF5::ItemViews Qt5::WebEngine Qt5::WebEngineWidgets KF5::KIOWidgets KF5::I18n KF5::WebEngineViewer)


set( adblockblockableitemsdialogtest_SRCS ${messageviewer_adblock_test_common_SRCS} adblockblockableitemsdialogtest.cpp)
add_executable( adblockblockableitemsdialogtest ${adblockblockableitemsdialogtest_SRCS})
add_test(adblockblockableitemsdialogtest adblockblockableitemsdialogtest)
ecm_mark_as_test(adblockblockableitemsdialogtest)
target_link_libraries( adblockblockableitemsdialogtest adblocklibprivate Qt5::Test Qt5::Widgets KF5::I18n KF5::MessageViewer
    KF5::PimCommon KF5::ItemViews Qt5::WebEngine Qt5::WebEngineWidgets KF5::ConfigCore KF5::KIOWidgets KF5::WebEngineViewer)


set( adblockblockableitemsjobtest_SRCS ${messageviewer_adblock_test_common_SRCS} adblockblockableitemsjobtest.cpp  ../adblockblockableitemsjob.cpp)
add_executable( adblockblockableitemsjobtest ${adblockblockableitemsjobtest_SRCS})
add_test(adblockblockableitemsjobtest adblockblockableitemsjobtest)
ecm_mark_as_test(adblockblockableitemsjobtest)
target_link_libraries( adblockblockableitemsjobtest adblocklibprivate Qt5::Test Qt5::WebEngine Qt5::WebEngineWidgets KF5::I18n KF5::WebEngineViewer)
