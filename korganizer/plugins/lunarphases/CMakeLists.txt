# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

########### next target ###############

add_library(lunarphases MODULE lunarphases.cpp lunarphases.h)


target_link_libraries(lunarphases
  KF5::Holidays
  KF5::EventViews
)

install(TARGETS
  lunarphases
  DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim${QT_MAJOR_VERSION}/korganizer
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
