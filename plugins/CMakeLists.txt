add_subdirectory(customtoolsplugins)
add_subdirectory(messageviewerplugins)
add_subdirectory(messageviewerheaderplugins)
add_subdirectory(storageservices)
add_subdirectory(messageviewer)

if (QTWEBENGINE_EXPERIMENTAL_OPTION)
    add_subdirectory(messageviewerwebengineurlinterceptor)
endif()
