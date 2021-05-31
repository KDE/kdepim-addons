
########### next target ###############

add_library(korg_thisdayinhistory MODULE)
target_sources(korg_thisdayinhistory PRIVATE
  thisdayinhistory.cpp
)


target_link_libraries(korg_thisdayinhistory
  KF5::EventViews
)

install(TARGETS
  korg_thisdayinhistory
  DESTINATION ${KDE_INSTALL_PLUGINDIR}
)

########### install files ###############

install(FILES
  thisdayinhistory.desktop
  DESTINATION ${KDE_INSTALL_KSERVICES5DIR}/korganizer
)
