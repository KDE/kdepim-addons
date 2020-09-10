add_definitions(-DTRANSLATION_DOMAIN=\"kaddressbook_importexportplugins\")

add_definitions(-DQGPGME_FOUND)

add_subdirectory(vcards)
add_subdirectory(csv)
add_subdirectory(gmx)
add_subdirectory(ldap)
add_subdirectory(ldif)
add_subdirectory(windows-contacts)
