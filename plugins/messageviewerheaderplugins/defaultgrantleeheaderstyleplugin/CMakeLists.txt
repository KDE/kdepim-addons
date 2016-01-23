set(messageviewer_defaultgrantleeheaderstyleplugin_SRCS
   defaultgrantleeheaderstyleplugin.cpp
   defaultgrantleeheaderstyleinterface.cpp
   defaultgrantleeheaderstrategy.cpp
)

kconfig_add_kcfg_files(messageviewer_defaultgrantleeheaderstyleplugin_SRCS
  settings/globalsettings_base.kcfgc
)


add_library(messageviewer_defaultgrantleeheaderstyleplugin MODULE ${messageviewer_defaultgrantleeheaderstyleplugin_SRCS})

target_link_libraries(messageviewer_defaultgrantleeheaderstyleplugin
  KF5::MessageViewer
  KF5::GrantleeTheme
  KF5::XmlGui
)

install(TARGETS messageviewer_defaultgrantleeheaderstyleplugin DESTINATION ${PLUGIN_INSTALL_DIR}/messageviewer)
