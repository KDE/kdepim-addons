# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(adblockblockableelementgui ${adblockblockableelementgui_SRCS})
target_sources(adblockblockableelementgui PRIVATE adblockblockableelementgui.cpp adblockblockableelementgui.h)
ecm_qt_declare_logging_category(adblockblockableelementgui HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME org.kde.pim.adblockinterceptor)
target_link_libraries(adblockblockableelementgui
  KPim6::MessageViewer  adblocklibprivate Qt::WebEngineWidgets KF6::ItemViews KF6::KIOWidgets KPim6::MessageViewer KPim6::WebEngineViewer
)

