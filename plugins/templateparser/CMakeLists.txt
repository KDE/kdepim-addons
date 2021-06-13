include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(BUILD_TESTING)
    add_subdirectory(tests)
    add_subdirectory(autotests)
endif()

kcoreaddons_add_plugin(templateparseraddressrequesterplugin JSON templateparseremailaddressrequesterakonadi.json INSTALL_NAMESPACE templateparser)

target_sources(templateparseraddressrequesterplugin PRIVATE
    templateparseremailaddressrequesterakonadi.cpp
    )


target_link_libraries(templateparseraddressrequesterplugin
    KF5::TemplateParser KF5::AkonadiContact
    )
