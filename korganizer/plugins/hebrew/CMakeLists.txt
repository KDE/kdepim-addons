
########### next target ###############

set(korg_hebrew_PART_SRCS
  qcalendarsystem.cpp
  configdialog.cpp
  converter.cpp
  hebrew.cpp
  holiday.cpp
  parsha.cpp
)

ecm_qt_declare_logging_category(korg_hebrew_PART_SRCS HEADER korganizer_hebrew_debug.h IDENTIFIER KORGANIZER_HEBREWPLUGIN_LOG CATEGORY_NAME org.kde.pim.korganizer_hebrew_plugin)

add_library(korg_hebrew MODULE ${korg_hebrew_PART_SRCS})

target_link_libraries(korg_hebrew
  KF5::EventViews
  KF5::I18n
  KF5::KDELibs4Support
)

install(TARGETS
  korg_hebrew
  DESTINATION ${KDE_INSTALL_PLUGINDIR}
)

########### install files ###############

install(FILES
  hebrew.desktop
  DESTINATION ${KDE_INSTALL_KSERVICES5DIR}/korganizer
)
