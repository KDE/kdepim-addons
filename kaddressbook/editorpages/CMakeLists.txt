
add_definitions(-DTRANSLATION_DOMAIN=\"cryptopageplugin\")

########### next target ###############
add_library(cryptopageplugin MODULE)
target_sources(cryptopageplugin PRIVATE cryptopageplugin.cpp cryptopageplugin.h)

target_link_libraries(cryptopageplugin KF5::Contacts KF5::ContactEditor KF5::Libkleo KF5::IconThemes KF5::I18n KF5::Completion Gpgmepp)

install(TARGETS cryptopageplugin DESTINATION ${KDE_INSTALL_LIBDIR}/contacteditor/editorpageplugins/)
