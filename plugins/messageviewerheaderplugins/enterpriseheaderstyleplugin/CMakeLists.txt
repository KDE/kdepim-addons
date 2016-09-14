set(messageviewer_enterpriseheaderstyleplugin_SRCS
   enterpriseheaderstyleplugin.cpp
   enterpriseheaderstyleinterface.cpp 
   enterpriseheaderstyle.cpp
)

kcoreaddons_add_plugin(messageviewer_enterpriseheaderstyleplugin JSON messageviewer_enterpriseheaderstyleplugin.json SOURCES
    ${messageviewer_enterpriseheaderstyleplugin_SRCS} INSTALL_NAMESPACE messageviewer)

target_link_libraries(messageviewer_enterpriseheaderstyleplugin
  KF5::MessageViewer 
  KF5::XmlGui
  KF5::I18n
)
