set(kaddressbook_mergecontactsplugin_SRCS
    mergecontactsplugininterface.cpp
    mergecontactsplugin.cpp
)


kcoreaddons_add_plugin(kaddressbook_mergecontactsplugin JSON kaddressbook_mergecontactsplugin.json SOURCES
    ${kaddressbook_mergecontactsplugin_SRCS} INSTALL_NAMESPACE kaddressbook/mainview)
if (COMPILE_WITH_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_mergecontactsplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kaddressbook_mergecontactsplugin
  KF5::PimCommon KF5::Completion  KF5::PimCommonAkonadi KF5::XmlGui kaddressbookmergelibprivate KF5::I18n
)
