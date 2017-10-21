set(pkpass_srcs
    pkpassfield.cpp
    pkpassfile.cpp
    pkpassboardingpass.cpp
    pkpass_plugin.cpp
)
qt5_add_resources(pkpass_srcs templates.qrc)

add_library(messageviewer_bodypartformatter_pkpass MODULE ${pkpass_srcs})
target_link_libraries(messageviewer_bodypartformatter_pkpass
  KF5::Archive
  KF5::Prison
  KF5::MessageViewer
  Grantlee5::Templates
)
install(TARGETS messageviewer_bodypartformatter_pkpass DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)
