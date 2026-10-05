# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

add_definitions(-DTRANSLATION_DOMAIN=\"kaddressbook_importexportplugins\")

add_definitions(-DQGPGME_FOUND)

add_subdirectory(vcards)
message(STATUS "csv needs to be port to qt6")
#add_subdirectory(csv)
add_subdirectory(gmx)
add_subdirectory(ldap)
add_subdirectory(ldif)
add_subdirectory(windows-contacts)
