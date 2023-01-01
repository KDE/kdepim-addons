# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(adblockblockableelementgui ${adblockblockableelementgui_SRCS})
target_sources(adblockblockableelementgui PRIVATE adblockblockableelementgui.cpp)
ecm_qt_declare_logging_category(adblockblockableelementgui HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME org.kde.pim.adblockinterceptor)
target_link_libraries(adblockblockableelementgui
  KF5::MessageViewer  adblocklibprivate Qt::WebEngineWidgets KF5::ItemViews KF5::KIOWidgets KF5::MessageViewer KF5::WebEngineViewer
)

