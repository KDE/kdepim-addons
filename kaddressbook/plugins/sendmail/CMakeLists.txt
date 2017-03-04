include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)


set(kaddressbook_sendmailplugin_SRCS
    sendmailplugininterface.cpp
    sendmailplugin.cpp
    mailsenderjob.cpp
)

ecm_qt_declare_logging_category(kaddressbook_sendmailplugin_SRCS HEADER kaddressbook_sendmailplugin_debug.h IDENTIFIER KADDRESSBOOK_SENDMAIL_LOG CATEGORY_NAME org.kde.pim.kaddressbook_sendmail)

kcoreaddons_add_plugin(kaddressbook_sendmailplugin JSON kaddressbook_sendmailplugin.json SOURCES
    ${kaddressbook_sendmailplugin_SRCS} INSTALL_NAMESPACE kaddressbook)


target_link_libraries(kaddressbook_sendmailplugin
  KF5::PimCommon KF5::Completion KF5::IconThemes KF5::PimCommonAkonadi KF5::XmlGui KF5::I18n
)

if (BUILD_TESTING)
   add_subdirectory(autotests)
endif()

