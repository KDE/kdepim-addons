########### next target ###############

set(korg_datenums_PART_SRCS
  configdialog.cpp
  datenums.cpp
)

add_library(korg_datenums MODULE ${korg_datenums_PART_SRCS})
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(korg_datenums PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(korg_datenums
  KF5::EventViews
)
install(TARGETS
  korg_datenums
  DESTINATION ${KDE_INSTALL_PLUGINDIR}
)

########### install files ###############

install(FILES
  datenums.desktop
  DESTINATION ${KDE_INSTALL_KSERVICES5DIR}/korganizer
)
