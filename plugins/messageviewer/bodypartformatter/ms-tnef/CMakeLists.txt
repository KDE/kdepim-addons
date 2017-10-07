
add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_application_mstnef_plugin\")

set(messageviewer_bodypartformatter_application_mstnef_SRCS application_ms-tnef.cpp)
ecm_qt_declare_logging_category(messageviewer_bodypartformatter_application_mstnef_SRCS HEADER ms_tnef_debug.h IDENTIFIER MS_TNEF_LOG CATEGORY_NAME org.kde.pim.ms_tnef)

add_library(messageviewer_bodypartformatter_application_mstnef MODULE ${messageviewer_bodypartformatter_application_mstnef_SRCS})

target_link_libraries(messageviewer_bodypartformatter_application_mstnef
  Qt5::Core
  KF5::CalendarCore
  KF5::CalendarUtils
  KF5::Tnef
  KF5::MessageCore
  KF5::MessageViewer
  KF5::IconThemes
  KF5::I18n
  Grantlee5::Templates
)
install(TARGETS messageviewer_bodypartformatter_application_mstnef DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)
