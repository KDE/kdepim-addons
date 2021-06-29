kcoreaddons_add_plugin(kmail_logactivitiesplugin INSTALL_NAMESPACE kmail/mainview)
target_sources(kmail_logactivitiesplugin PRIVATE
    logactivitiesplugin.cpp
    logactivitiesplugininterface.cpp
)


target_link_libraries(kmail_logactivitiesplugin
  KF5::PimCommon KF5::PimCommonAkonadi KF5::XmlGui KF5::Libkdepim KF5::I18n
)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_logactivitiesplugin PROPERTIES UNITY_BUILD ON)
endif()

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()
