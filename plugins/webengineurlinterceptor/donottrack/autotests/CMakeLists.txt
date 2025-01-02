# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set(donottrackpluginurlinterceptortest_SRCS donottrackpluginurlinterceptortest.cpp ../donottrackpluginurlinterceptor.cpp ../donottrackinterceptorinterface.cpp)
kconfig_add_kcfg_files(donottrackpluginurlinterceptortest_SRCS
  ../settings/donottracksettings.kcfgc
)
add_executable(donottrackpluginurlinterceptortest ${donottrackpluginurlinterceptortest_SRCS})
add_test(NAME donottrackpluginurlinterceptortest COMMAND donottrackpluginurlinterceptortest)
ecm_mark_as_test(donottrackpluginurlinterceptortest)
target_link_libraries(donottrackpluginurlinterceptortest Qt::Test Qt::Widgets KPim6::MessageViewer  Qt::WebEngineWidgets KPim6::WebEngineViewer)
