set(kmail_insertspecialcharactereditorplugin_SRCS
    insertspecialcharacterplugineditor.cpp
    insertspecialcharacterplugineditorinterface.cpp
)

add_library(kmail_insertspecialcharactereditorplugin MODULE ${kmail_insertspecialcharactereditorplugin_SRCS})

target_link_libraries(kmail_insertspecialcharactereditorplugin
  KF5::IconThemes KF5::MessageComposer KF5::XmlGui
)

install(TARGETS kmail_insertspecialcharactereditorplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kmail)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

