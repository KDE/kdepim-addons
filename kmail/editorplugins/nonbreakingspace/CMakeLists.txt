set(kmail_nonbreakingspaceeditorplugin_SRCS
    nonbreakingspaceplugineditor.cpp
    nonbreakingspaceplugineditorinterface.cpp
)

kcoreaddons_add_plugin(kmail_nonbreakingspaceeditorplugin JSON kmail_nonbreakingspaceeditorplugin.json SOURCES
    ${kmail_nonbreakingspaceeditorplugin_SRCS} INSTALL_NAMESPACE kmail/plugineditor)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_nonbreakingspaceeditorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_nonbreakingspaceeditorplugin
  KF5::MessageComposer KF5::XmlGui KF5::I18n
)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

