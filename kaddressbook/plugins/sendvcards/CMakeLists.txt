include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

set(kaddressbook_sendvcardsplugin_SRCS
    sendvcardsplugininterface.cpp
    sendvcardsplugin.cpp
    sendvcardsjob.cpp
)
ecm_qt_declare_logging_category(kaddressbook_sendvcardsplugin_SRCS HEADER kaddressbook_sendvcardsplugin_debug.h IDENTIFIER KADDRESSBOOK_SENDVCARDS_LOG CATEGORY_NAME log_kaddressbook_sendvcards)

add_library(kaddressbook_sendvcardsplugin MODULE ${kaddressbook_sendvcardsplugin_SRCS})

target_link_libraries(kaddressbook_sendvcardsplugin
  KF5::PimCommon KF5::Completion KF5::IconThemes KF5::MailCommon KF5::XmlGui KF5::MimeTreeParser KF5::I18n
)

install(TARGETS kaddressbook_sendvcardsplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kaddressbook)

if (BUILD_TESTING)
   add_subdirectory(autotests)
endif()

