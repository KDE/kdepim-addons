add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_bodypartformatter_pkpass\")

set(pkpass_srcs
    pkpass_plugin.cpp
)
qt5_add_resources(pkpass_srcs templates.qrc)
if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(pkpass_srcs HEADER pkpass_debug.h IDENTIFIER PKPASS_LOG CATEGORY_NAME org.kde.pim.pkpass)
else()
    ecm_qt_declare_logging_category(pkpass_srcs HEADER pkpass_debug.h IDENTIFIER PKPASS_LOG CATEGORY_NAME org.kde.pim.pkpass
        DESCRIPTION "kdepim-addons (pkpass formater)"
        EXPORT KDEPIMADDONS
        )
endif()


add_library(messageviewer_bodypartformatter_pkpass MODULE ${pkpass_srcs})
target_link_libraries(messageviewer_bodypartformatter_pkpass
  KF5::Archive
  KF5::Prison
  KF5::MessageViewer
  Grantlee5::Templates
  KPim::PkPass
)
install(TARGETS messageviewer_bodypartformatter_pkpass DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)

