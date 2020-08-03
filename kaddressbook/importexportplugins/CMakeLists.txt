add_definitions(-DTRANSLATION_DOMAIN=\"kaddressbook_importexportplugins\")

include_directories(${CMAKE_CURRENT_BINARY_DIR}/shared)

add_definitions(-DQGPGME_FOUND)

add_subdirectory(shared)

add_subdirectory(vcards)
add_subdirectory(csv)
add_subdirectory(gmx)
add_subdirectory(ldap)
add_subdirectory(ldif)
add_subdirectory(windows-contacts)
