add_definitions(-DTRANSLATION_DOMAIN=\"kaddressbook_importexportplugins\")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/shared)

add_subdirectory(shared)

add_subdirectory(vcards)
add_subdirectory(csv)
add_subdirectory(gmx)
add_subdirectory(ldap)  
add_subdirectory(ldif)

