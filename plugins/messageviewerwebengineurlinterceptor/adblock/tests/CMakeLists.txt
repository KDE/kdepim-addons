set(adblockblockableelementgui_SRCS adblockblockableelementgui.cpp ../adblockblockableitemsdialog.cpp ../adblockblockableitemswidget.cpp)
add_executable(adblockblockableelementgui ${adblockblockableelementgui_SRCS})
target_link_libraries(adblockblockableelementgui
  KF5::MessageViewer Qt5::WebEngine Qt5::WebEngineWidgets KF5::ItemViews KF5::KIOWidgets KF5::MessageViewer
)

