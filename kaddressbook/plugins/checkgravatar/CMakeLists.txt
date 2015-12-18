include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)


set(kaddressbook_checkgravatarplugin_SRCS
    checkgravatarplugininterface.cpp
    checkgravatarplugin.cpp
)

ecm_qt_declare_logging_category(kaddressbook_checkgravatarplugin_SRCS HEADER kaddressbook_checkgravatarplugin_debug.h IDENTIFIER KADDRESSBOOK_SENDMAIL_LOG CATEGORY_NAME log_kaddressbook_checkgravatar)

add_library(kaddressbook_checkgravatarplugin MODULE ${kaddressbook_checkgravatarplugin_SRCS})

target_link_libraries(kaddressbook_checkgravatarplugin
  KF5::PimCommon KF5::Completion KF5::IconThemes KF5::MailCommon KF5::XmlGui
)

install(TARGETS kaddressbook_checkgravatarplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kaddressbook)

