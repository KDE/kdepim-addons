kcoreaddons_add_plugin(kmail_antispamplugin JSON kmail_antispamplugin.json INSTALL_NAMESPACE kmail/mainview)
target_sources(kmail_antispamplugin PRIVATE
    antispamplugin.cpp
    antispamplugininterface.cpp
    ../common/antispamwizard.cpp
    ../common/antispam.qrc
)

target_link_libraries(kmail_antispamplugin
  KF5::PimCommonAkonadi KF5::Completion KF5::MailCommon KF5::XmlGui KF5::I18n KF5::GuiAddons
)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_antispamplugin PROPERTIES UNITY_BUILD ON)
endif()


if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()
