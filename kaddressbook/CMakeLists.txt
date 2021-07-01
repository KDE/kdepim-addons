# SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_subdirectory( editorpages )
add_subdirectory( plugins )
if (KPimAddressbookImportExport_FOUND)
	add_subdirectory( importexportplugins )
else()
	MESSAGE(STATUS "You need to build kaddressbook first and add install it on distro before building kdepim-addons. Otherwise import/export will be missing in kaddressbook")	
endif()	
