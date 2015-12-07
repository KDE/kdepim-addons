add_subdirectory(antispamplugin)
add_subdirectory(antivirusplugin)
install(FILES common/kmail.antispamrc common/kmail.antivirusrc  DESTINATION ${KDE_INSTALL_CONFDIR})
install(FILES common/pics/kmwizard.png common/pics/kmwizard.svg DESTINATION ${KDE_INSTALL_DATADIR}/kmail2/pics)
