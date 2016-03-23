set(messageviewer_adblock_test_common_SRCS)
ecm_qt_declare_logging_category(messageviewer_adblock_test_common_SRCS HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME log_adblockinterceptor)

ecm_add_test(adblockmanagertest.cpp ${messageviewer_adblock_test_common_SRCS}
    TEST_NAME adblockmanagertest
    NAME_PREFIX "messageviewer-urlinterceptor-"
    LINK_LIBRARIES Qt5::Test Qt5::Widgets adblocklibprivate KF5::ItemViews Qt5::WebEngine Qt5::WebEngineWidgets KF5::KIOWidgets
)


set( adblockpluginurlinterceptortest_SRCS ${messageviewer_adblock_test_common_SRCS} adblockpluginurlinterceptortest.cpp ../adblockpluginurlinterceptor.cpp ../adblockinterceptorinterface.cpp ../adblockpluginurlinterceptorconfigurewidget.cpp)
add_executable( adblockpluginurlinterceptortest ${adblockpluginurlinterceptortest_SRCS})
add_test(adblockpluginurlinterceptortest adblockpluginurlinterceptortest)
ecm_mark_as_test(adblockpluginurlinterceptortest)
target_link_libraries( adblockpluginurlinterceptortest Qt5::Test Qt5::Widgets adblocklibprivate KF5::MessageViewer Qt5::WebEngine Qt5::WebEngineWidgets KF5::ItemViews KF5::KIOWidgets KF5::XmlGui)

set( adblockpluginurlinterceptorconfigurewidgettest_SRCS ${messageviewer_adblock_test_common_SRCS} adblockpluginurlinterceptorconfigurewidgettest.cpp  )
add_executable( adblockpluginurlinterceptorconfigurewidgettest ${adblockpluginurlinterceptorconfigurewidgettest_SRCS})
add_test(adblockpluginurlinterceptorconfigurewidgettest adblockpluginurlinterceptorconfigurewidgettest)
ecm_mark_as_test(adblockpluginurlinterceptorconfigurewidgettest)
target_link_libraries( adblockpluginurlinterceptorconfigurewidgettest adblocklibprivate Qt5::Test Qt5::Widgets KF5::MessageViewer KF5::ItemViews Qt5::WebEngine Qt5::WebEngineWidgets KF5::KIOWidgets)


set( adblockblockableitemsdialogtest_SRCS ${messageviewer_adblock_test_common_SRCS} adblockblockableitemsdialogtest.cpp)
add_executable( adblockblockableitemsdialogtest ${adblockblockableitemsdialogtest_SRCS})
add_test(adblockblockableitemsdialogtest adblockblockableitemsdialogtest)
ecm_mark_as_test(adblockblockableitemsdialogtest)
target_link_libraries( adblockblockableitemsdialogtest adblocklibprivate Qt5::Test Qt5::Widgets KF5::I18n KF5::MessageViewer KF5::PimCommon KF5::ItemViews Qt5::WebEngine Qt5::WebEngineWidgets KF5::ConfigCore KF5::KIOWidgets)
