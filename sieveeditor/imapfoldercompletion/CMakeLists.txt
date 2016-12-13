if(BUILD_TESTING)
    add_subdirectory(tests)
    add_subdirectory(autotests)
endif()

set(imapfoldercompletionplugin_SRCS
    imapfoldercompletion.cpp
)

kcoreaddons_add_plugin(imapfoldercompletionplugin JSON imapfoldercompletion.json SOURCES
    ${imapfoldercompletionplugin_SRCS} INSTALL_NAMESPACE libksieve)
target_link_libraries(imapfoldercompletionplugin
  KF5::PimCommon KF5::Completion
)
