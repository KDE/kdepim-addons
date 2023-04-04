# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/../.. )
if (KDEPIM_RUN_AKONADI_TEST)
	set(KDEPIMLIBS_RUN_ISOLATED_TESTS TRUE)
	set(KDEPIMLIBS_RUN_SQLITE_ISOLATED_TESTS TRUE)

        add_akonadi_isolated_test_advanced( sendvcardsjobtest.cpp "../sendvcardsjob.cpp;../kaddressbook_sendvcardsplugin_debug.cpp" "KF6::Contacts;KPim6::PimCommon;KPim6::MimeTreeParser;KF6::I18n;KPim6::AkonadiContact;KF6::Service;KF6::KIOGui")
endif()
