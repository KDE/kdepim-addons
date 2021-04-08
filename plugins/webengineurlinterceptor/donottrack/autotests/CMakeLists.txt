set( donottrackpluginurlinterceptortest_SRCS donottrackpluginurlinterceptortest.cpp ../donottrackpluginurlinterceptor.cpp ../donottrackinterceptorinterface.cpp)
kconfig_add_kcfg_files(donottrackpluginurlinterceptortest_SRCS
  ../settings/donottracksettings.kcfgc
)
add_executable( donottrackpluginurlinterceptortest ${donottrackpluginurlinterceptortest_SRCS})
add_test(NAME donottrackpluginurlinterceptortest COMMAND donottrackpluginurlinterceptortest)
ecm_mark_as_test(donottrackpluginurlinterceptortest)
target_link_libraries( donottrackpluginurlinterceptortest Qt::Test Qt5::Widgets KF5::MessageViewer Qt5::WebEngine Qt5::WebEngineWidgets KF5::WebEngineViewer)
