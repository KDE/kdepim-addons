# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set(attendeeselector_SRCS
   ../attendeeselector.cpp
   main.cpp
)

ki18n_wrap_ui(attendeeselector_SRCS ../attendeeselector.ui)


add_executable(attendeeselector_gui ${attendeeselector_SRCS})
target_link_libraries(attendeeselector_gui
	KF5::PimCommon KF${KF_MAJOR_VERSION}::Completion KF${KF_MAJOR_VERSION}::KIOWidgets KF5::PimCommonAkonadi KF${KF_MAJOR_VERSION}::XmlGui KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::Codecs
)


