include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)


set(kaddressbook_sendmailplugin_SRCS
    sendmailplugininterface.cpp
    sendmailplugin.cpp
    mailsenderjob.cpp
)

ecm_qt_declare_logging_category(kaddressbook_sendmailplugin_SRCS HEADER kaddressbook_sendmailplugin_debug.h IDENTIFIER KADDRESSBOOK_SENDMAIL_LOG CATEGORY_NAME log_kaddressbook_sendmail)

add_library(kaddressbook_sendmailplugin MODULE ${kaddressbook_sendmailplugin_SRCS})

target_link_libraries(kaddressbook_sendmailplugin
  KF5::PimCommon KF5::Completion KF5::IconThemes KF5::MailCommon KF5::XmlGui
)

install(TARGETS kaddressbook_sendmailplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kaddressbook)
if (BUILD_TESTING)
   add_subdirectory(autotests)
endif()

