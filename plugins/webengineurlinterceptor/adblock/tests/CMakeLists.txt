set(messageviewer_adblock_test_common_SRCS)
ecm_qt_declare_logging_category(messageviewer_adblock_test_common_SRCS HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME org.kde.pim.adblockinterceptor)

set(adblockblockableelementgui_SRCS adblockblockableelementgui.cpp  ${messageviewer_adblock_test_common_SRCS})
add_executable(adblockblockableelementgui ${adblockblockableelementgui_SRCS})
target_link_libraries(adblockblockableelementgui
  KF5::MessageViewer Qt::WebEngine adblocklibprivate Qt::WebEngineWidgets KF5::ItemViews KF5::KIOWidgets KF5::MessageViewer KF5::WebEngineViewer
)

