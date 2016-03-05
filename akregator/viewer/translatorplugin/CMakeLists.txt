set(akregator_translatorplugin_SRCS
    akregatorplugintranslator.cpp
    akregatorplugintranslatorinterface.cpp
)

add_library(akregator_translatorplugin MODULE ${akregator_translatorplugin_SRCS})

target_link_libraries(akregator_translatorplugin
  KF5::MessageViewer KF5::XmlGui KF5::PimTextEdit
)

install(TARGETS akregator_translatorplugin DESTINATION ${PLUGIN_INSTALL_DIR}/akregator)
 
