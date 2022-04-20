# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

########### next target ###############

add_library(lunarphases MODULE lunarphases.cpp)

kcoreaddons_desktop_to_json(lunarphases lunarphases.desktop)

target_link_libraries(lunarphases
  KF5::Holidays
  KF5::EventViews
)

install(TARGETS
  lunarphases
  DESTINATION ${KDE_INSTALL_PLUGINDIR}/korganizer
)

########### install files ###############

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
