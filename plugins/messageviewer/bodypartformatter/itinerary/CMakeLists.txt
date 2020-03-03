set(itinerary_plugin_srcs
    itinerary_plugin.cpp
    itinerarymemento.cpp
    itineraryprocessor.cpp
    itineraryrenderer.cpp
    itineraryurlhandler.cpp
    itinerarykdeconnecthandler.cpp
    templates/templates.qrc
)
if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(itinerary_plugin_srcs HEADER itinerary_debug.h IDENTIFIER ITINERARY_LOG CATEGORY_NAME org.kde.pim.messageviewer.itinerary)
else()
    ecm_qt_declare_logging_category(itinerary_plugin_srcs HEADER itinerary_debug.h IDENTIFIER ITINERARY_LOG CATEGORY_NAME org.kde.pim.messageviewer.itinerary
        DESCRIPTION "kdepim-addons (Itinerary plugin)"
        EXPORT KDEPIMADDONS
        )
endif()


add_library(messageviewer_bodypartformatter_semantic MODULE ${itinerary_plugin_srcs})
target_compile_definitions(messageviewer_bodypartformatter_semantic PRIVATE -DTRANSLATION_DOMAIN=\"messageviewer_semantic_plugin\")
target_link_libraries(messageviewer_bodypartformatter_semantic
  KF5::KontactInterface
  KF5::MessageViewer
  KF5::CalendarSupport
  KF5::I18n
  KF5::GrantleeTheme
  Grantlee5::Templates
  Qt5::DBus
  KF5::Prison
  KPim::Itinerary
  KPim::PkPass
)
install(TARGETS messageviewer_bodypartformatter_semantic DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)
