# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

########### next target ###############

add_library(thisdayinhistory MODULE)
target_sources(thisdayinhistory PRIVATE
  thisdayinhistory.cpp
  thisdayinhistory.h
)

kcoreaddons_desktop_to_json(thisdayinhistory thisdayinhistory.desktop)

target_link_libraries(thisdayinhistory
  KF5::EventViews
)

install(TARGETS
  thisdayinhistory
  DESTINATION ${KDE_INSTALL_PLUGINDIR}/korganizer
)
