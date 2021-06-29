include_directories(${CMAKE_CURRENT_BINARY_DIR})

#if(BUILD_TESTING)
#    add_subdirectory(tests)
#    add_subdirectory(autotests)
#endif()

kcoreaddons_add_plugin(emailaddressselectionldapdialogplugin INSTALL_NAMESPACE akonadi)
target_sources(emailaddressselectionldapdialogplugin PRIVATE
    emailaddressselectionldapdialog.cpp
    )


target_link_libraries(emailaddressselectionldapdialogplugin
    KF5::I18n KF5::AkonadiContact KF5::PimCommonAkonadi
    )
