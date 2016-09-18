set(messageviewer_standardsheaderstyleplugin_SRCS
   standardsheaderstyleplugin.cpp
   standardsheaderstyleinterface.cpp
   standardheaderstrategy.cpp
)

kcoreaddons_add_plugin(messageviewer_standardsheaderstyleplugin JSON messageviewer_standardsheaderstyleplugin.json SOURCES
    ${messageviewer_standardsheaderstyleplugin_SRCS} INSTALL_NAMESPACE messageviewer)

target_link_libraries(messageviewer_standardsheaderstyleplugin
  KF5::MessageViewer
  KF5::XmlGui
  KF5::I18n
  KF5::GrantleeTheme
)
