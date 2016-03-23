set(messageviewer_adblock_test_common_SRCS)
ecm_qt_declare_logging_category(messageviewer_adblock_test_common_SRCS HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME log_adblockinterceptor)

ecm_add_test(adblockmanagertest.cpp ${messageviewer_adblock_test_common_SRCS}
    TEST_NAME adblockmanagertest
    NAME_PREFIX "messageviewer-urlinterceptor-"
    LINK_LIBRARIES Qt5::Test Qt5::Widgets adblocklibprivate KF5::ItemViews Qt5::WebEngine Qt5::WebEngineWidgets KF5::KIOWidgets
)


set( adblockpluginurlinterceptortest_SRCS ${messageviewer_adblock_test_common_SRCS} adblockpluginurlinterceptortest.cpp ../adblockpluginurlinterceptor.cpp ../adblockinterceptorinterface.cpp )
add_executable( adblockpluginurlinterceptortest ${adblockpluginurlinterceptortest_SRCS})
add_test(adblockpluginurlinterceptortest adblockpluginurlinterceptortest)
ecm_mark_as_test(adblockpluginurlinterceptortest)
target_link_libraries( adblockpluginurlinterceptortest Qt5::Test Qt5::Widgets adblocklibprivate KF5::MessageViewer Qt5::WebEngine Qt5::WebEngineWidgets KF5::ItemViews KF5::KIOWidgets KF5::XmlGui)
