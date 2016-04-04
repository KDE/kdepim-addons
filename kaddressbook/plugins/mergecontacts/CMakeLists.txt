set(kaddressbook_mergecontactsplugin_SRCS
    mergecontactsplugininterface.cpp
    mergecontactsplugin.cpp
)

add_library(kaddressbook_mergecontactsplugin MODULE ${kaddressbook_mergecontactsplugin_SRCS})

target_link_libraries(kaddressbook_mergecontactsplugin
  KF5::PimCommon KF5::Completion KF5::IconThemes KF5::MailCommon KF5::XmlGui kaddressbookmergelibprivate KF5::I18n
)

install(TARGETS kaddressbook_mergecontactsplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kaddressbook)
