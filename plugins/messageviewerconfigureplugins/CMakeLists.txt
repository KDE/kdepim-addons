add_definitions(-DTRANSLATION_DOMAIN=\"messageviewerconfiguresettingsplugins\")

add_subdirectory(gravatar)

if (KMAIL_DKIM_CONFIGURE_DIALOG_BUILD)
    add_subdirectory(dkim-verify)
endif()
