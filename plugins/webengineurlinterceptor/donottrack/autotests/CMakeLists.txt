# SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set( donottrackpluginurlinterceptortest_SRCS donottrackpluginurlinterceptortest.cpp ../donottrackpluginurlinterceptor.cpp ../donottrackinterceptorinterface.cpp)
kconfig_add_kcfg_files(donottrackpluginurlinterceptortest_SRCS
  ../settings/donottracksettings.kcfgc
)
add_executable( donottrackpluginurlinterceptortest ${donottrackpluginurlinterceptortest_SRCS})
add_test(NAME donottrackpluginurlinterceptortest COMMAND donottrackpluginurlinterceptortest)
ecm_mark_as_test(donottrackpluginurlinterceptortest)
target_link_libraries( donottrackpluginurlinterceptortest Qt${QT_MAJOR_VERSION}::Test Qt${QT_MAJOR_VERSION}::Widgets KF5::MessageViewer Qt${QT_MAJOR_VERSION}::WebEngine Qt${QT_MAJOR_VERSION}::WebEngineWidgets KF5::WebEngineViewer)
