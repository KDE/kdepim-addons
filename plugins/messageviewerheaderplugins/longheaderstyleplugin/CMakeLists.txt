set(messageviewer_longheaderstyleplugin_SRCS
   longheaderstyleplugin.cpp
   longheaderstyleinterface.cpp
)

kcoreaddons_add_plugin(messageviewer_longheaderstyleplugin JSON messageviewer_longheaderstyleplugin.json SOURCES
    ${messageviewer_longheaderstyleplugin_SRCS} INSTALL_NAMESPACE messageviewer/headerstyle)

target_link_libraries(messageviewer_longheaderstyleplugin
  KF5::MessageViewer
  KF5::XmlGui
  KF5::I18n
)
