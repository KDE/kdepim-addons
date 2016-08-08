set(kmail_nonbreakingspaceeditorplugin_SRCS
    nonbreakingspaceplugineditor.cpp
    nonbreakingspaceplugineditorinterface.cpp
)

add_library(kmail_nonbreakingspaceeditorplugin MODULE ${kmail_nonbreakingspaceeditorplugin_SRCS})

target_link_libraries(kmail_nonbreakingspaceeditorplugin
  KF5::IconThemes KF5::MessageComposer KF5::XmlGui KF5::I18n
)

install(TARGETS kmail_nonbreakingspaceeditorplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kmail)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

