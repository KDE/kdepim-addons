add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_bodypartformatter_pkpass\")

set(pkpass_srcs
    pkpassfield.cpp
    pkpassfile.cpp
    pkpassboardingpass.cpp
    pkpass_plugin.cpp
)
qt5_add_resources(pkpass_srcs templates.qrc)
ecm_qt_declare_logging_category(pkpass_srcs HEADER pkpass_debug.h IDENTIFIER PKPASS_LOG CATEGORY_NAME org.kde.pim.pkpass)

add_library(messageviewer_bodypartformatter_pkpass MODULE ${pkpass_srcs})
target_link_libraries(messageviewer_bodypartformatter_pkpass
  KF5::Archive
  KF5::Prison
  KF5::MessageViewer
  Grantlee5::Templates
)
install(TARGETS messageviewer_bodypartformatter_pkpass DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)

install(FILES application-vnd-apple-pkpass.xml DESTINATION ${XDG_MIME_INSTALL_DIR})
update_xdg_mimetypes(${XDG_MIME_INSTALL_DIR})
