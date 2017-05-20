include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(BUILD_TESTING)
    add_subdirectory(tests)
    add_subdirectory(autotests)
endif()


set(regexpeditorlineeditplugin_SRCS
    regexpeditorlineedit.cpp
    )

kcoreaddons_add_plugin(regexpeditorlineeditplugin JSON regexepeditorlineedit.json SOURCES
    ${regexpeditorlineeditplugin_SRCS} INSTALL_NAMESPACE libksieve)

target_link_libraries(regexpeditorlineeditplugin
    KF5::I18n KF5::KSieveUi
    )
