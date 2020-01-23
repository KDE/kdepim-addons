set(messageviewer_fancyheaderstyleplugin_SRCS
   fancyheaderstyleplugin.cpp
   fancyheaderstyleinterface.cpp
   fancyheaderstyle.cpp
)

kcoreaddons_add_plugin(messageviewer_fancyheaderstyleplugin JSON messageviewer_fancyheaderstyleplugin.json SOURCES
    ${messageviewer_fancyheaderstyleplugin_SRCS} INSTALL_NAMESPACE messageviewer/headerstyle)

target_link_libraries(messageviewer_fancyheaderstyleplugin
  KF5::MessageViewer
  KF5::XmlGui
  KF5::I18n
)
