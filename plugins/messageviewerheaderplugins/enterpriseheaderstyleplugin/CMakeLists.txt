set(messageviewer_enterpriseheaderstyleplugin_SRCS
   enterpriseheaderstyleplugin.cpp
   enterpriseheaderstyleinterface.cpp 
   enterpriseheaderstyle.cpp
)

add_library(messageviewer_enterpriseheaderstyleplugin MODULE ${messageviewer_enterpriseheaderstyleplugin_SRCS})

target_link_libraries(messageviewer_enterpriseheaderstyleplugin
  KF5::MessageViewer 
  KF5::XmlGui
  KF5::I18n
)

install(TARGETS messageviewer_enterpriseheaderstyleplugin DESTINATION ${PLUGIN_INSTALL_DIR}/messageviewer)
