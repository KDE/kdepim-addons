set(kaddressbook_searchduplicatesplugin_SRCS
    searchduplicatesplugininterface.cpp
    searchduplicatesplugin.cpp
)

kcoreaddons_add_plugin(kaddressbook_searchduplicatesplugin JSON kaddressbook_searchduplicatesplugin.json SOURCES
    ${kaddressbook_searchduplicatesplugin_SRCS} INSTALL_NAMESPACE kaddressbook/mainview)
if (COMPILE_WITH_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_searchduplicatesplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kaddressbook_searchduplicatesplugin
  KF5::PimCommon KF5::Completion  KF5::PimCommonAkonadi KF5::XmlGui kaddressbookmergelibprivate KF5::I18n
)
