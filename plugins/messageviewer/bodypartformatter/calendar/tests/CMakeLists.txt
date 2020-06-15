set(attendeeselector_SRCS
   ../attendeeselector.cpp
   main.cpp
)

ki18n_wrap_ui(attendeeselector_SRCS ../attendeeselector.ui)


add_executable(attendeeselector_gui ${attendeeselector_SRCS})
target_link_libraries(attendeeselector_gui
	KF5::PimCommon KF5::Completion KF5::KIOWidgets KF5::PimCommonAkonadi KF5::XmlGui KF5::I18n
)


