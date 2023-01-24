# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/../.. )
if (KDEPIM_RUN_AKONADI_TEST)
	set(KDEPIMLIBS_RUN_ISOLATED_TESTS TRUE)
	set(KDEPIMLIBS_RUN_SQLITE_ISOLATED_TESTS TRUE)

	add_akonadi_isolated_test_advanced( mailsenderjobtest.cpp "../mailsenderjob.cpp;../kaddressbook_sendmailplugin_debug.cpp" "KF${KF_MAJOR_VERSION}::Contacts;KF${KF_MAJOR_VERSION}::Codecs;KF${KF_MAJOR_VERSION}::I18n;KF${KF_MAJOR_VERSION}::Codecs")
endif()
