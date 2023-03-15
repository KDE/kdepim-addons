# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set(messageviewer_adblock_test_common_SRCS)
ecm_qt_declare_logging_category(messageviewer_adblock_test_common_SRCS HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME org.kde.pim.adblockinterceptor)


set( adblockpluginurlinterceptorconfigurewidgettest_SRCS ${messageviewer_adblock_test_common_SRCS} adblockpluginurlinterceptorconfigurewidgettest.cpp)
add_executable( adblockpluginurlinterceptorconfigurewidgettest ${adblockpluginurlinterceptorconfigurewidgettest_SRCS})
add_test(NAME adblockpluginurlinterceptorconfigurewidgettest COMMAND adblockpluginurlinterceptorconfigurewidgettest)
ecm_mark_as_test(adblockpluginurlinterceptorconfigurewidgettest)
target_link_libraries( adblockpluginurlinterceptorconfigurewidgettest adblocklibprivate Qt::Test Qt::Widgets KPim${KF_MAJOR_VERSION}::MessageViewer
    KF${KF_MAJOR_VERSION}::ItemViews  Qt::WebEngineWidgets KF${KF_MAJOR_VERSION}::KIOWidgets KF${KF_MAJOR_VERSION}::I18n KPim${KF_MAJOR_VERSION}::WebEngineViewer)


set( adblockblockableitemsdialogtest_SRCS ${messageviewer_adblock_test_common_SRCS} adblockblockableitemsdialogtest.cpp)
add_executable( adblockblockableitemsdialogtest ${adblockblockableitemsdialogtest_SRCS})
add_test(NAME adblockblockableitemsdialogtest COMMAND adblockblockableitemsdialogtest)
ecm_mark_as_test(adblockblockableitemsdialogtest)
target_link_libraries( adblockblockableitemsdialogtest adblocklibprivate Qt::Test Qt::Widgets KF${KF_MAJOR_VERSION}::I18n KPim${KF_MAJOR_VERSION}::MessageViewer
    KPim${KF_MAJOR_VERSION}::PimCommon KF${KF_MAJOR_VERSION}::ItemViews  Qt::WebEngineWidgets KF${KF_MAJOR_VERSION}::ConfigCore KF${KF_MAJOR_VERSION}::KIOWidgets KPim${KF_MAJOR_VERSION}::WebEngineViewer)


set( adblockblockableitemsjobtest_SRCS ${messageviewer_adblock_test_common_SRCS} adblockblockableitemsjobtest.cpp)
add_executable( adblockblockableitemsjobtest ${adblockblockableitemsjobtest_SRCS})
add_test(NAME adblockblockableitemsjobtest COMMAND adblockblockableitemsjobtest)
ecm_mark_as_test(adblockblockableitemsjobtest)
target_link_libraries( adblockblockableitemsjobtest adblocklibprivate Qt::Test  Qt::WebEngineWidgets KF${KF_MAJOR_VERSION}::I18n KPim${KF_MAJOR_VERSION}::WebEngineViewer)


set( adblockresulttest_SRCS ${messageviewer_adblock_test_common_SRCS} adblockresulttest.cpp )
add_executable( adblockresulttest ${adblockresulttest_SRCS})
add_test(NAME adblockresulttest COMMAND adblockresulttest)
ecm_mark_as_test(adblockresulttest)
target_link_libraries( adblockresulttest adblocklibprivate Qt::Test  Qt::WebEngineWidgets KPim${KF_MAJOR_VERSION}::WebEngineViewer)
