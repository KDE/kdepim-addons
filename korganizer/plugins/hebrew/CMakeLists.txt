
########### next target ###############
find_package(KF5KDELibs4Support ${KF_MIN_VERSION} CONFIG REQUIRED) #for the korganizer hebrew plugin
add_library(hebrew MODULE)
target_sources(hebrew PRIVATE
  qcalendarsystem.cpp
  configdialog.cpp
  converter.cpp
  hebrew.cpp
  holiday.cpp
  parsha.cpp
)

ecm_qt_declare_logging_category(hebrew HEADER korganizer_hebrew_debug.h IDENTIFIER KORGANIZER_HEBREWPLUGIN_LOG CATEGORY_NAME org.kde.pim.korganizer_hebrew_plugin)


target_link_libraries(hebrew
  KF5::EventViews
  KF${KF_MAJOR_VERSION}::I18n
  KF5::KDELibs4Support
)

install(TARGETS
  hebrew
  DESTINATION ${KDE_INSTALL_PLUGINDIR}/korganizer
)
