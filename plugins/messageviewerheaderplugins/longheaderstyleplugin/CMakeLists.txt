kcoreaddons_add_plugin(messageviewer_longheaderstyleplugin JSON messageviewer_longheaderstyleplugin.json INSTALL_NAMESPACE messageviewer/headerstyle)
target_sources(messageviewer_longheaderstyleplugin PRIVATE
   longheaderstyleplugin.cpp
   longheaderstyleinterface.cpp
)


target_link_libraries(messageviewer_longheaderstyleplugin
  KF5::MessageViewer
  KF5::XmlGui
  KF5::I18n
)
