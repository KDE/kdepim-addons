set(kaddressbook_sendvcardsplugin_SRCS
    sendvcardsplugininterface.cpp
    sendvcardsplugin.cpp
    sendvcardsjob.cpp
)

add_library(kaddressbook_sendvcardsplugin MODULE ${kaddressbook_sendvcardsplugin_SRCS})

target_link_libraries(kaddressbook_sendvcardsplugin
  KF5::PimCommon KF5::Completion KF5::IconThemes KF5::MailCommon KF5::XmlGui
)

install(TARGETS kaddressbook_sendvcardsplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kaddressbook)

MESSAGE(STATUS "reactivate autotests")
if (BUILD_TESTING)
   #add_subdirectory(autotests)
endif()

