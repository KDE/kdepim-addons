kcoreaddons_add_plugin(messageviewer_standardsheaderstyleplugin INSTALL_NAMESPACE messageviewer/headerstyle)
target_sources(messageviewer_standardsheaderstyleplugin PRIVATE
   standardsheaderstyleplugin.cpp
   standardsheaderstyleinterface.cpp
   standardheaderstrategy.cpp
)


target_link_libraries(messageviewer_standardsheaderstyleplugin
  KF5::MessageViewer
  KF5::XmlGui
  KF5::I18n
  KF5::GrantleeTheme
)
