set(messageviewer_fancyheaderstyleplugin_SRCS
   fancyheaderstyleplugin.cpp
   fancyheaderstyleinterface.cpp
   fancyheaderstyle.cpp
)

add_library(messageviewer_fancyheaderstyleplugin MODULE ${messageviewer_fancyheaderstyleplugin_SRCS})

target_link_libraries(messageviewer_fancyheaderstyleplugin
  KF5::MessageViewer
  KF5::GrantleeTheme
  KF5::XmlGui
  KF5::IconThemes
  KF5::I18n
)

install(TARGETS messageviewer_fancyheaderstyleplugin DESTINATION ${PLUGIN_INSTALL_DIR}/messageviewer)
