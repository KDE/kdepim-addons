kcoreaddons_add_plugin(messageviewer_gravatarconfigplugin JSON messageviewer_gravatarconfigplugin.json INSTALL_NAMESPACE messageviewer/configuresettings)
target_sources(messageviewer_gravatarconfigplugin PRIVATE
   gravatarconfiguresettingspluginwidget.cpp
   gravatarconfiguresettingsplugin.cpp
   gravatarconfiguresettingsplugindialog.cpp
)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_gravatarconfigplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_gravatarconfigplugin
  KF5::MessageViewer
  KF5::PimCommon
  KF5::Gravatar
  KF5::I18n
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

