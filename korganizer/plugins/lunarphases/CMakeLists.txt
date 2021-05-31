########### next target ###############

add_library(korg_lunarphases MODULE lunarphases.cpp)

target_link_libraries(korg_lunarphases
  KF5::Holidays
  KF5::EventViews
)

install(TARGETS
  korg_lunarphases
  DESTINATION ${KDE_INSTALL_PLUGINDIR}
)

########### install files ###############

install(FILES
  lunarphases.desktop
  DESTINATION ${KDE_INSTALL_KSERVICES5DIR}/korganizer
)
