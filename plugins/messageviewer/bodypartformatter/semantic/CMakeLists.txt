set(semantic_plugin_srcs
    semantic_plugin.cpp
    semanticmemento.cpp
    semanticprocessor.cpp
    semanticrenderer.cpp
    semanticurlhandler.cpp
)
ecm_qt_declare_logging_category(semantic_plugin_srcs HEADER semantic_debug.h IDENTIFIER SEMANTIC_LOG CATEGORY_NAME org.kde.pim.messageviewer.semantic)
qt5_add_resources(semantic_plugin_srcs templates.qrc)

add_library(messageviewer_bodypartformatter_semantic MODULE ${semantic_plugin_srcs})
target_compile_definitions(messageviewer_bodypartformatter_semantic PRIVATE -DTRANSLATION_DOMAIN=\"messageviewer_semantic_plugin\")
target_link_libraries(messageviewer_bodypartformatter_semantic
  KF5::MessageViewer
  KF5::CalendarSupport
  KF5::I18n
  Grantlee5::Templates
  Qt5::DBus
  KF5::Prison
  KPim::Itinerary
  KPim::PkPass
)
install(TARGETS messageviewer_bodypartformatter_semantic DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)
