# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

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
  DESTINATION ${KDE_INSTALL_KSERVICESDIR}/korganizer
)

include(ECMInstallIcons)
ecm_install_icons(
    ICONS
        pics/sc-status-moon-phase-first-quarter.svg
        pics/sc-status-moon-phase-full.svg
        pics/sc-status-moon-phase-last-quarter.svg
        pics/sc-status-moon-phase-new.svg
    DESTINATION ${KDE_INSTALL_ICONDIR}
    THEME hicolor
)
