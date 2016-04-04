set(kmail_zoomtexteditorplugin_SRCS
    zoomtextplugineditor.cpp
    zoomtextplugineditorinterface.cpp
)

ecm_qt_declare_logging_category(kmail_zoomtexteditorplugin_SRCS HEADER zoomtexteditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_ZOOMTEXT_PLUGIN_LOG CATEGORY_NAME log_kmail_zoomtexteditorplugin)

add_library(kmail_zoomtexteditorplugin MODULE ${kmail_zoomtexteditorplugin_SRCS})

target_link_libraries(kmail_zoomtexteditorplugin
  KF5::IconThemes KF5::MessageComposer KF5::XmlGui KF5::I18n
)

install(TARGETS kmail_zoomtexteditorplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kmail)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

