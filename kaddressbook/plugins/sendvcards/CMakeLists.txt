include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

set(kaddressbook_sendvcardsplugin_SRCS
    sendvcardsplugininterface.cpp
    sendvcardsplugin.cpp
    sendvcardsjob.cpp
)
ecm_qt_declare_logging_category(kaddressbook_sendvcardsplugin_SRCS HEADER kaddressbook_sendvcardsplugin_debug.h IDENTIFIER KADDRESSBOOK_SENDVCARDS_LOG CATEGORY_NAME log_kaddressbook_sendvcards)


kcoreaddons_add_plugin(kaddressbook_sendvcardsplugin JSON kaddressbook_sendvcardsplugin.json SOURCES
    ${kaddressbook_sendvcardsplugin_SRCS} INSTALL_NAMESPACE kaddressbook)


target_link_libraries(kaddressbook_sendvcardsplugin
  KF5::PimCommon KF5::Completion KF5::IconThemes KF5::MailCommon KF5::XmlGui KF5::MimeTreeParser KF5::I18n
)

if (BUILD_TESTING)
   add_subdirectory(autotests)
endif()

