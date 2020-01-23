set(messageviewer_translatorplugin_SRCS
    viewerplugintranslator.cpp
    viewerplugintranslatorinterface.cpp
)

kcoreaddons_add_plugin(messageviewer_translatorplugin JSON messageviewer_translatorplugin.json SOURCES
    ${messageviewer_translatorplugin_SRCS} INSTALL_NAMESPACE messageviewer/viewercommonplugin)

target_link_libraries(messageviewer_translatorplugin
  KF5::MessageViewer KF5::XmlGui KF5::PimTextEdit KF5::I18n
)
 
