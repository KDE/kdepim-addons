set(messageviewer_allheaderstyleplugin_SRCS
   allheaderstyleplugin.cpp
   allheaderstyleinterface.cpp
   allheaderstrategy.cpp
)

add_library(messageviewer_allheaderstyleplugin MODULE ${messageviewer_allheaderstyleplugin_SRCS})

target_link_libraries(messageviewer_allheaderstyleplugin
  KF5::MessageViewer
  KF5::XmlGui
  KF5::GrantleeTheme
  KF5::I18n
)

install(TARGETS messageviewer_allheaderstyleplugin DESTINATION ${PLUGIN_INSTALL_DIR}/messageviewer)
