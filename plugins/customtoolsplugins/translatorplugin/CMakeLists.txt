kcoreaddons_add_plugin(pimcommon_translatorplugin INSTALL_NAMESPACE pimcommon/customtools)
target_sources(pimcommon_translatorplugin PRIVATE
   translatorplugin.cpp
   translatorview.cpp
)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(pimcommon_translatorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(pimcommon_translatorplugin
  KF5::PimCommon
  KF5::PimTextEdit
  KF5::XmlGui
  KF5::I18n
)
