
ecm_add_test(adblockmanagertest.cpp
    TEST_NAME adblockmanagertest
    NAME_PREFIX "messageviewer-urlinterceptor-"
    LINK_LIBRARIES Qt5::Test Qt5::Widgets adblocklibprivate
)

ecm_add_test(adblockpluginurlinterceptortest.cpp
    TEST_NAME adblockpluginurlinterceptortest
    NAME_PREFIX "messageviewer-urlinterceptor-"
    LINK_LIBRARIES Qt5::Test Qt5::Widgets adblocklibprivate
)
