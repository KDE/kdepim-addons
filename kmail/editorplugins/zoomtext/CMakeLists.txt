set(kmail_zoomtexteditorplugin_SRCS
    zoomtextplugineditor.cpp
    zoomtextplugineditorinterface.cpp
)

add_library(kmail_zoomtexteditorplugin MODULE ${kmail_zoomtexteditorplugin_SRCS})

target_link_libraries(kmail_zoomtexteditorplugin
  KF5::IconThemes KF5::MessageComposer KF5::XmlGui
)

install(TARGETS kmail_zoomtexteditorplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kmail)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

