include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(BUILD_TESTING)
    add_subdirectory(tests)
    add_subdirectory(autotests)
endif()


set(templateparserplugin_SRCS
    templateparseremailaddressrequesterakonadi.cpp
    )

kcoreaddons_add_plugin(templateparseraddressrequesterplugin JSON templateparseremailaddressrequesterakonadi.json SOURCES
    ${templateparserplugin_SRCS} INSTALL_NAMESPACE templateparser)

target_link_libraries(templateparseraddressrequesterplugin
    KF5::TemplateParser KF5::Completion KF5::I18n KF5::AkonadiContact
    )
