set(kmail_autocorrectioneditorplugin_SRCS
    autocorrectionplugineditor.cpp
    autocorrectionplugineditorinterface.cpp
    autocorrectionplugineditorjob.cpp
    )

add_library(kmail_autocorrectioneditorplugin MODULE ${kmail_autocorrectioneditorplugin_SRCS})

target_link_libraries(kmail_autocorrectioneditorplugin
    KF5::IconThemes KF5::MessageComposer KF5::XmlGui KF5::I18n
    )

install(TARGETS kmail_autocorrectioneditorplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kmail)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

