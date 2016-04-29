add_definitions(-DTRANSLATION_DOMAIN=\"kmail_plugins\")
add_subdirectory(antispamplugin)
add_subdirectory(antivirusplugin)
add_subdirectory(common/avscripts)
#Laurent disable for the moment
#add_subdirectory(mailmergeplugin)
install(FILES common/kmail.antispamrc common/kmail.antivirusrc  DESTINATION ${KDE_INSTALL_CONFDIR})
install(FILES common/pics/kmwizard.png common/pics/kmwizard.svg DESTINATION ${KDE_INSTALL_DATADIR}/kmail2/pics)
