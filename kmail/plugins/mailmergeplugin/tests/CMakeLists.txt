# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set(mailmergewidget_gui_SRCS mailmergewidgettest_gui.cpp)
add_executable(mailmergewidget_gui ${mailmergewidget_gui_SRCS})
target_link_libraries(
    mailmergewidget_gui
    KF6::KIOCore
    KF6::KIOWidgets
    KPim6::PimCommon
    KF6::I18n
    mailmerge
)
