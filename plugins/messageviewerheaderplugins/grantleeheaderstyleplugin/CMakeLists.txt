kcoreaddons_add_plugin(messageviewer_grantleeheaderstyleplugin INSTALL_NAMESPACE messageviewer/headerstyle)
target_sources(messageviewer_grantleeheaderstyleplugin PRIVATE
   grantleeheaderstyleplugin.cpp
   grantleeheaderstyleinterface.cpp
   grantleeheaderstrategy.cpp
)

target_link_libraries(messageviewer_grantleeheaderstyleplugin
  KF5::MessageViewer
  KF5::GrantleeTheme
  KF5::XmlGui
)
