set(kaddressbook_searchduplicatesplugin_SRCS
    searchduplicatesplugininterface.cpp
    searchduplicatesplugin.cpp
)

add_library(kaddressbook_searchduplicatesplugin MODULE ${kaddressbook_searchduplicatesplugin_SRCS})

target_link_libraries(kaddressbook_searchduplicatesplugin
  KF5::PimCommon KF5::Completion KF5::IconThemes KF5::MailCommon KF5::XmlGui kaddressbookmergelibprivate KF5::I18n
)

install(TARGETS kaddressbook_searchduplicatesplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kaddressbook)
