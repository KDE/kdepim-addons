# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set(mailmergewidget_gui_SRCS mailmergewidgettest_gui.cpp)
add_executable(mailmergewidget_gui ${mailmergewidget_gui_SRCS})
target_link_libraries(mailmergewidget_gui
  KF${KF_MAJOR_VERSION}::KIOCore
  KF${KF_MAJOR_VERSION}::KIOWidgets
  KF5::PimCommon
  KF${KF_MAJOR_VERSION}::I18n
  mailmerge
)

