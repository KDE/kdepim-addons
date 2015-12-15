set(kaddressbook_sendmailplugin_SRCS
    sendmailplugininterface.cpp
    sendmailplugin.cpp
    mailsenderjob.cpp
)

add_library(kaddressbook_sendmailplugin MODULE ${kaddressbook_sendmailplugin_SRCS})

target_link_libraries(kaddressbook_sendmailplugin
  KF5::PimCommon KF5::Completion KF5::IconThemes KF5::MailCommon KF5::XmlGui
)

install(TARGETS kaddressbook_sendmailplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kaddressbook)
if (BUILD_TESTING)
   add_subdirectory(autotests)
endif()

