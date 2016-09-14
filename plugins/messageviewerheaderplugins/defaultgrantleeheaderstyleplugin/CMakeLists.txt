set(messageviewer_defaultgrantleeheaderstyleplugin_SRCS
   defaultgrantleeheaderstyleplugin.cpp
   defaultgrantleeheaderstyleinterface.cpp
   defaultgrantleeheaderstrategy.cpp
)

kconfig_add_kcfg_files(messageviewer_defaultgrantleeheaderstyleplugin_SRCS
  settings/globalsettings_base.kcfgc
)

kcoreaddons_add_plugin(messageviewer_defaultgrantleeheaderstyleplugin JSON messageviewer_defaultgrantleeheaderstyleplugin.json SOURCES
    ${messageviewer_defaultgrantleeheaderstyleplugin_SRCS} INSTALL_NAMESPACE messageviewer)

target_link_libraries(messageviewer_defaultgrantleeheaderstyleplugin
  KF5::MessageViewer
  KF5::GrantleeTheme
  KF5::XmlGui
)

install(DIRECTORY theme/5.2 DESTINATION ${KDE_INSTALL_DATADIR}/messageviewer/defaultthemes/ )
