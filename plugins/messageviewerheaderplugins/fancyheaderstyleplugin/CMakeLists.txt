kcoreaddons_add_plugin(messageviewer_fancyheaderstyleplugin JSON messageviewer_fancyheaderstyleplugin.json INSTALL_NAMESPACE messageviewer/headerstyle)
target_sources(messageviewer_fancyheaderstyleplugin PRIVATE
   fancyheaderstyleplugin.cpp
   fancyheaderstyleinterface.cpp
   fancyheaderstyle.cpp
)


target_link_libraries(messageviewer_fancyheaderstyleplugin
  KF5::MessageViewer
  KF5::XmlGui
  KF5::I18n
)
