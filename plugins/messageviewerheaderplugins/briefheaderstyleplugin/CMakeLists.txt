kcoreaddons_add_plugin(messageviewer_briefheaderstyleplugin INSTALL_NAMESPACE messageviewer/headerstyle)
target_sources(messageviewer_briefheaderstyleplugin PRIVATE
   briefheaderstyleplugin.cpp
   briefheaderstyleinterface.cpp 
   briefheaderstyle.cpp
   briefheaderstrategy.cpp
)


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_briefheaderstyleplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_briefheaderstyleplugin
  KF5::MessageViewer
  KF5::XmlGui
  KF5::I18n
)
