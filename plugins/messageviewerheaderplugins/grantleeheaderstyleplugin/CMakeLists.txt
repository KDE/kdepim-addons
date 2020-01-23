set(messageviewer_grantleeheaderstyleplugin_SRCS
   grantleeheaderstyleplugin.cpp
   grantleeheaderstyleinterface.cpp
   grantleeheaderstrategy.cpp
)
kcoreaddons_add_plugin(messageviewer_grantleeheaderstyleplugin JSON messageviewer_grantleeheaderstyleplugin.json SOURCES
    ${messageviewer_grantleeheaderstyleplugin_SRCS} INSTALL_NAMESPACE messageviewer/headerstyle)

target_link_libraries(messageviewer_grantleeheaderstyleplugin
  KF5::MessageViewer
  KF5::GrantleeTheme
  KF5::XmlGui
)
