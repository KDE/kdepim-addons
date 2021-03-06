add_library(messageviewer_bodypartformatter_semantic MODULE)

target_sources(messageviewer_bodypartformatter_semantic PRIVATE
    itinerary_plugin.cpp
    itinerarymemento.cpp
    itineraryprocessor.cpp
    itineraryrenderer.cpp
    itineraryurlhandler.cpp
    itinerarykdeconnecthandler.cpp
    templates/templates.qrc
    )
ecm_qt_declare_logging_category(messageviewer_bodypartformatter_semantic HEADER itinerary_debug.h IDENTIFIER ITINERARY_LOG CATEGORY_NAME org.kde.pim.messageviewer.itinerary
    DESCRIPTION "kdepim-addons (Itinerary plugin)"
    EXPORT KDEPIMADDONS
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_bodypartformatter_semantic PROPERTIES UNITY_BUILD ON)
endif()

target_compile_definitions(messageviewer_bodypartformatter_semantic PRIVATE -DTRANSLATION_DOMAIN=\"messageviewer_semantic_plugin\")
target_link_libraries(messageviewer_bodypartformatter_semantic
    KF5::KontactInterface
    KF5::MessageViewer
    KF5::CalendarSupport
    KF5::I18n
    KF5::GrantleeTheme
    Grantlee5::Templates
    Qt::DBus
    KF5::Prison
    KPim::Itinerary
    KPim::PkPass
    )
install(TARGETS messageviewer_bodypartformatter_semantic DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)
