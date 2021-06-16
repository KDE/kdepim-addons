kcoreaddons_add_plugin(messageviewer_translatorplugin JSON messageviewer_translatorplugin.json INSTALL_NAMESPACE messageviewer/viewercommonplugin)
target_sources(messageviewer_translatorplugin PRIVATE
    viewerplugintranslator.cpp
    viewerplugintranslatorinterface.cpp
)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_translatorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_translatorplugin
  KF5::MessageViewer KF5::XmlGui KF5::PimTextEdit KF5::I18n
)
 
