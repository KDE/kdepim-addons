set(mailmergewidget_gui_SRCS mailmergewidgettest_gui.cpp)
add_executable(mailmergewidget_gui ${mailmergewidget_gui_SRCS})
target_link_libraries(mailmergewidget_gui
  KF5::KIOCore
  KF5::KIOWidgets
  KF5::PimCommon
  KF5::I18n
  mailmerge
)

