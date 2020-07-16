add_definitions(-DTRANSLATION_DOMAIN=\"messageviewerconfiguresettingsplugins\")

add_subdirectory(gravatar)

set(CMAKE_REQUIRED_LIBRARIES KF5::MessageViewer)
add_subdirectory(dkim-verify)
add_subdirectory(expireaccounttrashfolder)
