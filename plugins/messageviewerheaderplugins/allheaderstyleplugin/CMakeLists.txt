set(messageviewer_allheaderstyleplugin_SRCS
   allheaderstyleplugin.cpp
   allheaderstyleinterface.cpp
   allheaderstrategy.cpp
)

kcoreaddons_add_plugin(messageviewer_allheaderstyleplugin JSON messageviewer_allheaderstyleplugin.json SOURCES
    ${messageviewer_allheaderstyleplugin_SRCS} INSTALL_NAMESPACE messageviewer)


target_link_libraries(messageviewer_allheaderstyleplugin
  KF5::MessageViewer
  KF5::XmlGui
  KF5::I18n
)
