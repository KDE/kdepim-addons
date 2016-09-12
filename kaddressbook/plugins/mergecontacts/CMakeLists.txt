set(kaddressbook_mergecontactsplugin_SRCS
    mergecontactsplugininterface.cpp
    mergecontactsplugin.cpp
)


kcoreaddons_add_plugin(kaddressbook_mergecontactsplugin JSON kaddressbook_mergecontactsplugin.json SOURCES
    ${kaddressbook_mergecontactsplugin_SRCS} INSTALL_NAMESPACE kaddressbook)

target_link_libraries(kaddressbook_mergecontactsplugin
  KF5::PimCommon KF5::Completion KF5::IconThemes KF5::MailCommon KF5::XmlGui kaddressbookmergelibprivate KF5::I18n
)
