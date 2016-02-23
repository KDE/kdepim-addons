
ecm_add_test(adblockmanagertest.cpp
    TEST_NAME adblockmanagertest
    NAME_PREFIX "messageviewer-urlinterceptor-"
    LINK_LIBRARIES Qt5::Test Qt5::Widgets adblocklibprivate
)


set( adblockpluginurlinterceptortest_SRCS adblockpluginurlinterceptortest.cpp ../adblockpluginurlinterceptor.cpp ../adblockinterceptorinterface.cpp ../adblockpluginurlinterceptorconfigurewidget.cpp)
add_executable( adblockpluginurlinterceptortest ${adblockpluginurlinterceptortest_SRCS})
add_test(adblockpluginurlinterceptortest adblockpluginurlinterceptortest)
ecm_mark_as_test(adblockpluginurlinterceptortest)
target_link_libraries( adblockpluginurlinterceptortest Qt5::Test Qt5::Widgets adblocklibprivate KF5::MessageViewer Qt5::WebEngine Qt5::WebEngineWidgets)
