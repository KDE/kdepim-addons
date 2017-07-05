add_definitions(-DTRANSLATION_DOMAIN=\"kmailtransport_plugins\")
if (NOT WIN32)
    add_subdirectory(sendmail)
endif()
