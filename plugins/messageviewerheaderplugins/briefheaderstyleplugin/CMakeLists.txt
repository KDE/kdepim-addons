set(messageviewer_briefheaderstyleplugin_SRCS
   briefheaderstyleplugin.cpp
   briefheaderstyleinterface.cpp 
   briefheaderstyle.cpp
   briefheaderstrategy.cpp
)

kcoreaddons_add_plugin(messageviewer_briefheaderstyleplugin JSON messageviewer_briefheaderstyleplugin.json SOURCES
    ${messageviewer_briefheaderstyleplugin_SRCS} INSTALL_NAMESPACE messageviewer/headerstyle)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_briefheaderstyleplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_briefheaderstyleplugin
  KF5::MessageViewer
  KF5::XmlGui
  KF5::I18n
)
