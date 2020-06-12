include_directories(${CMAKE_CURRENT_BINARY_DIR})

#if(BUILD_TESTING)
#    add_subdirectory(tests)
#    add_subdirectory(autotests)
#endif()

set(emailaddressselectionldapdialog_SRCS
    emailaddressselectionldapdialog.cpp
    )

kcoreaddons_add_plugin(emailaddressselectionldapdialogplugin JSON emailaddressselectionldapdialog.json SOURCES
    ${emailaddressselectionldapdialog_SRCS} INSTALL_NAMESPACE akonadi)

target_link_libraries(emailaddressselectionldapdialogplugin
    KF5::I18n KF5::AkonadiContact KF5::PimCommonAkonadi
    )
