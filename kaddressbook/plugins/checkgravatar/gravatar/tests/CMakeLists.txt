
set(gravatarupdatedialog_gui_SRCS gravatarupdatedialog_gui.cpp ../widgets/gravatarupdatedialog.cpp ../widgets/gravatarupdatewidget.cpp ../job/gravatarupdatejob.cpp)
add_executable(gravatarupdatedialog_gui ${gravatarupdatedialog_gui_SRCS})
ecm_mark_as_test(gravatarupdatedialog_gui)
target_link_libraries(gravatarupdatedialog_gui
  Qt5::Gui
  KF5::PimCommon
  KF5::Gravatar
  KF5::I18n
)

