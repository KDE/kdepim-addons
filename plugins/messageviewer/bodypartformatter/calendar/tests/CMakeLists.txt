# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set(attendeeselector_SRCS
   ../attendeeselector.cpp
   main.cpp
)

ki18n_wrap_ui(attendeeselector_SRCS ../attendeeselector.ui)


add_executable(attendeeselector_gui ${attendeeselector_SRCS})
target_link_libraries(attendeeselector_gui
	KPim6::PimCommon KF6::Completion KF6::KIOWidgets KPim6::PimCommonAkonadi KF6::XmlGui KF6::I18n KF6::Codecs
)


