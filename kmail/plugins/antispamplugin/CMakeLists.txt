set(kmail_antispamplugins_SRCS
    antispamplugin.cpp
)

add_library(kmail_antispamplugins MODULE ${kmail_antispamplugins_SRCS})

target_link_libraries(kmail_antispamplugins
  KF5::PimCommon
)

install(TARGETS kmail_antispamplugins DESTINATION ${PLUGIN_INSTALL_DIR}/kmail)
#kcoreaddons_desktop_to_json(messageviewer_translatorplugin messageviewer_translatorplugin.desktop)

