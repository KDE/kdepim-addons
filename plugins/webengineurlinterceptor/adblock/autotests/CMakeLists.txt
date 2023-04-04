# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set(messageviewer_adblock_test_common_SRCS)
ecm_qt_declare_logging_category(messageviewer_adblock_test_common_SRCS HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME org.kde.pim.adblockinterceptor)

ecm_add_test(adblockmanagertest.cpp ${messageviewer_adblock_test_common_SRCS}
    TEST_NAME adblockmanagertest
    NAME_PREFIX "messageviewer-urlinterceptor-"
    LINK_LIBRARIES Qt::Test Qt::Widgets adblocklibprivate KF6::ItemViews  Qt::WebEngineWidgets KF6::KIOWidgets KF6::I18n KPim6::WebEngineViewer
)

ecm_add_test(adblockinterceptorinterfacetest.cpp ${messageviewer_adblock_test_common_SRCS} ../adblockinterceptorinterface.cpp
    TEST_NAME adblockinterceptorinterface
    NAME_PREFIX "messageviewer-urlinterceptor-"
    LINK_LIBRARIES Qt::Test Qt::Widgets adblocklibprivate KF6::ItemViews  Qt::WebEngineWidgets KF6::KIOWidgets KF6::I18n KPim6::WebEngineViewer KF6::XmlGui
)

set( adblockpluginurlinterceptortest_SRCS ${messageviewer_adblock_test_common_SRCS} adblockpluginurlinterceptortest.cpp ../adblockpluginurlinterceptor.cpp ../adblockinterceptorinterface.cpp )
add_executable( adblockpluginurlinterceptortest ${adblockpluginurlinterceptortest_SRCS})
add_test(NAME adblockpluginurlinterceptortest COMMAND adblockpluginurlinterceptortest)
ecm_mark_as_test(adblockpluginurlinterceptortest)
target_link_libraries( adblockpluginurlinterceptortest Qt::Test Qt::Widgets adblocklibprivate KPim6::MessageViewer
     Qt::WebEngineWidgets KF6::ItemViews KF6::KIOWidgets KF6::XmlGui KF6::I18n KPim6::WebEngineViewer)
