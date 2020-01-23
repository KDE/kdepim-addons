set(kmail_logactivitiesplugin_SRCS
    logactivitiesplugin.cpp
    logactivitiesplugininterface.cpp
)

kcoreaddons_add_plugin(kmail_logactivitiesplugin JSON kmail_logactivitiesplugin.json SOURCES
    ${kmail_logactivitiesplugin_SRCS} INSTALL_NAMESPACE kmail/mainview)

target_link_libraries(kmail_logactivitiesplugin
  KF5::PimCommon KF5::PimCommonAkonadi KF5::XmlGui KF5::Libkdepim KF5::I18n
)
if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()
