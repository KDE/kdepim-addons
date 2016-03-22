set(adblockblockableelementgui_SRCS adblockblockableelementgui.cpp)
add_executable(adblockblockableelementgui ${adblockblockableelementgui_SRCS})
target_link_libraries(adblockblockableelementgui
  KF5::MessageViewer Qt5::WebEngine Qt5::WebEngineWidgets
)

