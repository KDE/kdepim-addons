add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_bodypartformatter_pkpass\")
add_library(messageviewer_bodypartformatter_pkpass MODULE)

target_sources(messageviewer_bodypartformatter_pkpass PRIVATE
    pkpass_plugin.cpp
    templates.qrc
    )
ecm_qt_declare_logging_category(messageviewer_bodypartformatter_pkpass HEADER pkpass_debug.h IDENTIFIER PKPASS_LOG CATEGORY_NAME org.kde.pim.pkpass
    DESCRIPTION "kdepim-addons (pkpass formater)"
    EXPORT KDEPIMADDONS
    )


target_link_libraries(messageviewer_bodypartformatter_pkpass
    KF5::Archive
    KF5::Prison
    KF5::MessageViewer
    Grantlee5::Templates
    KPim::PkPass
    )
install(TARGETS messageviewer_bodypartformatter_pkpass DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)

