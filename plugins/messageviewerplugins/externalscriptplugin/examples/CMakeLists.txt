file(GLOB externalScriptDesktopFiles "*.desktop")
install(FILES ${externalScriptDesktopFiles} DESTINATION "${KDE_INSTALL_DATADIR}/messageviewerplugins/")
