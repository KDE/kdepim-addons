# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(adblockblockableelementgui ${adblockblockableelementgui_SRCS})
target_sources(adblockblockableelementgui PRIVATE adblockblockableelementgui.cpp adblockblockableelementgui.h)
ecm_qt_declare_logging_category(adblockblockableelementgui HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME org.kde.pim.adblockinterceptor)
target_link_libraries(adblockblockableelementgui
  KPim${KF_MAJOR_VERSION}::MessageViewer  adblocklibprivate Qt::WebEngineWidgets KF${KF_MAJOR_VERSION}::ItemViews KF${KF_MAJOR_VERSION}::KIOWidgets KPim${KF_MAJOR_VERSION}::MessageViewer KPim${KF_MAJOR_VERSION}::WebEngineViewer
)

